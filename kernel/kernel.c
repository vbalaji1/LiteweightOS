#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include "core.h"
#include "vga.h"
#include "multiboot.h"
#include "gdt.h"
#include "tss.h"
#include "mmap.h"
#include "p_alloc.h"


void kernel_main(multiboot_info_t* mb) {
	vga_init(vga_light_cyan);
	vga_print_string("Loaded VGA Successully\n"); 
	gdt_init();
	vga_print_string("Loaded GDT Succesfully\n");

	mmap(mb);

	for (size_t i = 0; i < 32599; i++) {
		vga_print_string(itoa_hex((unsigned int) allocate_pframe())); vga_print_newline();
	}
	free_pframe(0);


	free_pframe(0x8000);
	free_pframe(0x8a0000);

	vga_print_string(itoa_hex((unsigned int) allocate_pframe())); vga_print_newline();
	vga_print_string(itoa_hex((unsigned int) allocate_pframe())); vga_print_newline();

	free_pframe(0);

	vga_print_string(itoa_hex((unsigned int) allocate_pframe())); vga_print_newline();
	vga_print_string(itoa_hex((unsigned int) allocate_pframe())); vga_print_newline();


	

	 

}
 