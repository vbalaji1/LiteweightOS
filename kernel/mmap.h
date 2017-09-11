#ifndef _MMAP_H
#define _MMAP_H

#include <stdint.h>
#include "core.h"
#include "vga.h"
#include "multiboot.h"

#define PAGE_SIZE 4096

struct free_mem_range {
	uint32_t base;
	uint32_t end;
	uint8_t* bitmap;
};

extern uintptr_t k_end;
struct free_mem_range* free_mmap; 
uint8_t* pageframe_bitmap;
uint8_t* bitmap_end;
size_t free_mem_regions; 
size_t bitmap_size; 
size_t total_pages;

void mmap(multiboot_info_t*);


#endif 