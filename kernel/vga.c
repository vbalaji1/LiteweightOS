#include "vga.h"

volatile uint8_t* video_memory;
const size_t video_width = 160;
const size_t video_height = 24;
video_color vga_text_color; 
size_t x = 0; 
size_t y = 0;
//Detects whether the monitor is color or monochrome.
uint16_t detect_video_card_type(void) {
	const uint16_t* bios_hardware_ptr = (const uint16_t*) 0x410;
	return *bios_hardware_ptr & 0x30;
}

//Returns VGA pointer address based on monitor type.
uint8_t* set_video_memory(void) {
	switch (detect_video_card_type()) {
		case 0x20:
			return (uint8_t*) 0xb8000;
		case 0x30:
			return (uint8_t*) 0xb80000;
		default:
			return (uint8_t*) 0x0;
	}
}

void disable_cursor(void) {
	outb(0x3D4, 0x0A);
	outb(0x3D5, 0x3f);
}

void vga_init(video_color txt_color) {
	video_memory = (volatile uint8_t*) set_video_memory();
	disable_cursor();
	vga_clear();
	vga_text_color = txt_color;
} 

void vga_scroll(void) {
	for (size_t m = 0; m <= video_height; m++) {
		for (size_t j = 0; j <= video_width; j++) {
			video_memory[m * video_width + j] = video_memory[(m + 1) * video_width + j];
		}
	}
	y--;
}

void vga_clear(void) {
	for (size_t i = 0; i <= video_height; i++) {
		for (size_t j = 0; j <= video_width; j++) {
			size_t index = i * video_width + j;
			video_memory[index] = index % 2 == 0 ? ' ' : vga_black;
		}
	}
}

void vga_print_string(const char* string) {
	while (*string != 0) {
		if (y > video_height) {
			vga_scroll();
		}
		if (*string == '\n') {
			x = 0;
			y++;
			string++;
			continue;
		}
		video_memory[y * video_width + x] = *string++;
		video_memory[y * video_width + x + 1] = vga_text_color;
		x += 2;
		if (x >= video_width) {
			x = 0;
			y++; 
		}
	}
}

void vga_print_newline(void) {
	vga_print_string("\n");
}

void vga_chg_txt_color(video_color new_color) {
	vga_text_color = new_color;
}