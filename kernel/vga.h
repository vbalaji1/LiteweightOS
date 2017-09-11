#ifndef VIDEO_H_
#define VIDEO_H_

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h> 
#include "core.h"

extern volatile uint8_t* video_memory; 
extern volatile char* video_base;

extern const size_t video_width;
extern const size_t video_height;

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


uint16_t detect_video_card_type(void);
uint8_t* set_video_memory(void);
void disable_cursor(void); 
void vga_init(video_color);
void vga_scroll(void);
void vga_clear(void);
void vga_print_string(const char*);
void vga_print_newline(void);
void vga_chg_txt_color(video_color);

#endif
