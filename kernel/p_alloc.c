#include "p_alloc.h"

size_t pages_allocated;
size_t current_mem_zone; 
size_t block_counter;


static void set_bit(uint8_t* byte, unsigned int bit) {
	*byte |= 1 << bit;
}

static void clear_bit(uint8_t* byte, unsigned int bit) {
	*byte &= ~(1 << bit);
}

static uint8_t check_bit(uint8_t* byte, unsigned int bit) {
	uint8_t ret;
	ret = ((*byte) >> bit) & 1;
	return ret;
} 

uint32_t allocate_pframe(void) {
	if (pages_allocated >= total_pages) {
		vga_print_string("Out of memory!\n");
		return 0x100000; //Error code since this is the start of the kernel
	}
	uint8_t* curr_bitmap = free_mmap[current_mem_zone].bitmap + block_counter;  
	while ((free_mmap[current_mem_zone].base + (block_counter * PAGE_SIZE * 8)) < free_mmap[current_mem_zone].end) {
		for (size_t i = 0; i < 8; i++) {
			if (check_bit(curr_bitmap, i) == 0) {
				if ((free_mmap[current_mem_zone].base + (block_counter * PAGE_SIZE * 8) + (PAGE_SIZE * i)) < free_mmap[current_mem_zone].end) {
					set_bit(curr_bitmap, i);  
					pages_allocated++;
					return free_mmap[current_mem_zone].base + (block_counter * PAGE_SIZE * 8) + (PAGE_SIZE * i);
				} else {
					current_mem_zone++;
					block_counter = 0;
					return allocate_pframe();
				}
			}
		}
		block_counter++;
		curr_bitmap++;
	}
	current_mem_zone++;
	block_counter = 0;
	return allocate_pframe(); 
}

void free_pframe(uint32_t pframe) {
	if (check_pframe(pframe) == 0) {
		return;
	}
	for (size_t i = 0; i < free_mem_regions; i++) {
		if (pframe >= free_mmap[i].base && pframe <= free_mmap[i].end) {
			uint8_t* bmp = free_mmap[i].bitmap;
			size_t block_position = (pframe - free_mmap[i].base) / (PAGE_SIZE * 8);
			unsigned int bit_position = (pframe - ((block_position * PAGE_SIZE * 8) + free_mmap[i].base)) / PAGE_SIZE; 
			if (i < current_mem_zone || (i == current_mem_zone &&block_position < block_counter)) {
				//vga_print_string(itoa_d(i)); vga_print_string("   "); vga_print_string(itoa_d(block_position)); vga_print_string("\n");
				current_mem_zone = i;
				block_counter = block_position; //So it starts searching from the earliest place where the last page was freed
			}
			clear_bit(bmp + block_position, bit_position);
			pages_allocated--;
			return;
		}
	}
}

unsigned int check_pframe(uint32_t pframe) {
	for (size_t i = 0; i < free_mem_regions; i++) {
		if (pframe >= free_mmap[i].base && pframe <= free_mmap[i].end) {
			uint8_t* bmp = free_mmap[i].bitmap;
			size_t block_position = (pframe - free_mmap[i].base) / (PAGE_SIZE * 8);
			unsigned int bit_position = (pframe - ((block_position * PAGE_SIZE * 8) + free_mmap[i].base)) / PAGE_SIZE; 
			return (unsigned int) check_bit(bmp + block_position, bit_position);
		}
	}
	return 1;
}