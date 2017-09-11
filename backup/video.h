#include <stdint.h>
#ifndef VIDEO_H_
#define VIDEO_H_

//Detects whether the monitor is color or monochrome.
uint16_t detect_video_card_type(void) {
	const uint16_t* bios_hardware_ptr = (const uint16_t*) 0x410;
	return *bios_hardware_ptr & 0x30;
}

//Returns VGA pointer address based on monitor type.
char* set_video_memory(void) {
	switch (detect_video_card_type()) {
		case 0x20:
			return (char*) 0xb8000;
		case 0x30:
			return (char*) 0xb80000;
	}
}
volatile char* video_memory = 0x0;

const size_t video_column_size = 80;
const size_t video_row_size = 25;

typedef enum video_color {
	vga_black = 0,
	vga_blue = 1,
	vga_green = 2,
	vga_cyan = 3,
	vga_red = 4,
	vga_magenta = 5,
	vga_brown = 6,
	vga_light_gray = 7,
	vga_dark_gray = 8,
	vga_light_blue = 9,
	vga_light_green = 10,
	vga_light_cyan = 11,
	vga_light_red = 12,
	vga_light_magenta = 13,
	vga_yellow = 14,
	vga_white = 15,
} video_color;

#endif
