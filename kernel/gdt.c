#include <stdint.h>
#include <stddef.h>
#include "core.h"
#include "tss.h"
#include "gdt.h"
#include "vga.h"

struct gdt_descriptor gdt[6];
struct gdt_ptr lgdt_ptr;
struct tss tss_entry;

void set_null_descriptor(void) {
	gdt[0].limit_0_15 = 0;
	gdt[0].base_0_15 = 0;
	gdt[0].base_16_23 = 0;
	gdt[0].access = 0;
	gdt[0].limit_flags = 0;
	gdt[0].base_24_31 = 0;
};


void set_gdt_descriptor(int entry, uint8_t access) {
	gdt[entry].limit_0_15 = 0xFFFF;
	gdt[entry].base_0_15 = 0;
	gdt[entry].base_16_23 = 0;
	gdt[entry].access = access;
	gdt[entry].limit_flags = 0xCF;
	gdt[entry].base_24_31 = 0; 
}

void set_tss_flags(void) {
	uint32_t tss_base = (uint32_t) &tss_entry;
	uint32_t limit =  sizeof(tss_entry);
	gdt[5].limit_0_15 = limit & 0xFFFF;
	gdt[5].base_0_15 = tss_base & 0xFFFF;
	gdt[5].base_16_23 = (tss_base >> 16) & 0xFF;
	gdt[5].access = 0xE9;
	gdt[5].limit_flags = 0x40;
	gdt[5].base_24_31 =  (tss_base >> 24) & 0xFF;
}

void set_tss_members(void) {
	tss_entry.ss0 = 0x10;
	tss_entry.esp0 = 0x0;
	tss_entry.iomap_base = sizeof(tss_entry);
}

void gdt_init(void) {
	lgdt_ptr.base = (uintptr_t) gdt;
	lgdt_ptr.limit = (sizeof(struct gdt_descriptor) * 6) - 1;
	set_null_descriptor();
	set_gdt_descriptor(1, 0x9A); //Kernel Code
	set_gdt_descriptor(2, 0x92); //Kernel Data
	set_gdt_descriptor(3, 0xFA); //User Code
	set_gdt_descriptor(4, 0xF2); //User Data
	set_tss_flags(); 
	memset(&tss_entry, 0, sizeof(tss_entry));
	set_tss_members();
	load_gdt(&lgdt_ptr); 
	load_tss();
}

void set_kstack(uint32_t kstack) {
	tss_entry.esp0 = kstack;
}

