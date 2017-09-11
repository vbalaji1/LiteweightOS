#include "mmap.h" 
  
#define FOUR_GB 4294967296

uintptr_t RESERVED_ZONE_BASE;

struct free_mem_range* free_mmap; 
struct free_mem_range* struct_allocator;

size_t free_mem_regions;

uint8_t* pageframe_bitmap;
uint8_t* bitmap_end;
size_t bitmap_size;

uintptr_t first_free_page; 
size_t total_pages;

void check_structs(void) {
	for (size_t i = 0; i < free_mem_regions; i++) {
		vga_print_string(itoa_d(free_mmap[i].base)); vga_print_newline();
		vga_print_string(itoa_d(free_mmap[i].end)); vga_print_newline();
		vga_print_string(itoa_hex((uintptr_t) free_mmap[i].bitmap)); vga_print_newline();
	}
	vga_print_string("Number of free memory regions:   "); vga_print_string(itoa_d(free_mem_regions)); vga_print_newline();
}

void create_mem_struct(uint32_t base, uint32_t end) { 
	struct_allocator->base = base;
	struct_allocator->end = end;
	struct_allocator++;
} 

void mmap(multiboot_info_t* mb) { 
	vga_print_string("Mem lower at:    "); vga_print_string(itoa_hex(mb->mem_lower));
	vga_print_newline();
	vga_print_string("Mem upper at:    "); vga_print_string(itoa_hex(mb->mem_upper));
	vga_print_newline();

	size_t total_detected_ram = 0;
	size_t usable_ram = 0;
	uint32_t end_address = mb->mmap_addr + mb->mmap_length;
	multiboot_memory_map_t* mmp = (multiboot_memory_map_t*) mb->mmap_addr;

	vga_print_string("Kernel start address:   "); vga_print_string(itoa_hex(1048576)); 
	vga_print_newline();
	vga_print_string("Kernel end address:   "); vga_print_string(itoa_hex((unsigned int) &k_end));
	vga_print_newline(); 

	RESERVED_ZONE_BASE = (uintptr_t) &k_end; 
	free_mmap = (struct free_mem_range*) RESERVED_ZONE_BASE; 
	struct_allocator = free_mmap;

	while ((uintptr_t)mmp < end_address) {
		vga_print_string("Mmap base address:   "); vga_print_string(itoa_hex(mmp->addr));
		vga_print_string("    ");
		vga_print_string("Mmap length:   "); vga_print_string(itoa_hex(mmp->len));
		vga_print_string("    ");
		if (mmp->type == 1) {
			vga_print_string("Available");
			free_mem_regions++;
			create_mem_struct(mmp->addr, mmp->addr + mmp->len - 1);
			usable_ram += mmp->len;   
		} else if (mmp->type == 2) {
			vga_print_string("Reserved");
		}
		total_detected_ram += mmp->len;
		vga_print_newline();
		mmp = (multiboot_memory_map_t*) ((uint32_t)mmp + sizeof(mmp->size) + mmp->size);    
	}

	vga_print_string("Total detected RAM:   "); vga_print_string(itoa_d(total_detected_ram)); vga_print_string("  Bytes");
	vga_print_newline();
	vga_print_string("Total usable RAM:   "); vga_print_string(itoa_d(usable_ram)); vga_print_string("  Bytes");
	vga_print_newline();  

	if (free_mem_regions >= 50) {
		vga_print_string("WARNING: Memory fragmentation is high -- expect delayed memory performance"); vga_print_newline(); 
	}
	
	pageframe_bitmap = (uint8_t*) struct_allocator; //Bitmap begins at end of structs describing free memory zones
	bitmap_size = (FOUR_GB / PAGE_SIZE) / 8; //Allocates size of bitmap for all 4GB
	memset(pageframe_bitmap, 0, bitmap_size); //Initializes all of bitmap to 0 (free)
	first_free_page = (uintptr_t) pageframe_bitmap + bitmap_size + 1; //Sets address of first free page to end of bitmap
	first_free_page = (first_free_page + PAGE_SIZE) - (first_free_page % PAGE_SIZE); //4K Aligns first free page address 

	struct free_mem_range* free_mmap_cpy = free_mmap; 
	uint8_t* pageframe_bitmap_cpy = pageframe_bitmap;
	for (size_t i = 0; i < free_mem_regions; i++) {
		if (first_free_page >= free_mmap[i].base && first_free_page <= free_mmap[i].end) {
			free_mmap[i].base = first_free_page;
		}
	}
	for (size_t i = 0; i < free_mem_regions; i++) {
		size_t region_size = ((free_mmap_cpy->end) - (free_mmap_cpy->base)) / PAGE_SIZE; 
		total_pages += region_size;
		vga_print_string(itoa_d(total_pages)); vga_print_newline();
		free_mmap_cpy->bitmap = pageframe_bitmap_cpy;
		pageframe_bitmap_cpy += (((region_size + 7) / 8) + 1);
		free_mmap_cpy++;
	}
	//vga_print_string(itoa_d(bitmap_end)); vga_print_newline();
	check_structs();
	vga_print_string(itoa_d(first_free_page)); vga_print_newline();
	//vga_print_string(itoa_hex(pageframe_bitmap)); vga_print_newline();


	

	
}


