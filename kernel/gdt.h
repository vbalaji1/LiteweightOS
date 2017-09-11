#ifndef _GDT_H
#define _GDT_H

struct gdt_descriptor {
	uint16_t limit_0_15;
	uint16_t base_0_15;
	uint8_t base_16_23;
	uint8_t access; // 7-0, present, privl (2 bits), executable, direction/conforming, read/write, accessed 
	uint8_t limit_flags; //3-0 limit 16-19, 7-4 granularity, size, 64-bit code segment, available
	uint8_t base_24_31;  
} __attribute__((packed));

struct gdt_ptr {
	uint16_t limit;
	uint32_t base;
} __attribute__((packed));

void set_null_descriptor(void);
void set_gdt_descriptor(int, uint8_t);
void set_tss_flags(void);
void set_tss_members(void);
void gdt_init(void);
void set_kstack(uint32_t);

extern void load_gdt(struct gdt_ptr*); 

#endif