#ifndef CORE_H_
#define CORE_H_

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

void outb(uint16_t, uint8_t);
uint8_t inb(uint16_t);
void xor_swap(char*, char*);
size_t strlen(const char*);
void reverse(char*);
char* itoa(int);
char* itoa_d(unsigned int);
char* itoa_hex(unsigned int);
void* memset(void* s, int c, size_t n); 

#endif