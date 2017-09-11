#ifndef _P_ALLOC_H
#define _P_ALLOC_H

#include <stdint.h>
#include "mmap.h"
#include "vga.h"

size_t pages_allocated; 

uint32_t allocate_pframe(void);
void free_pframe(uint32_t);
unsigned int check_pframe(uint32_t);


#endif