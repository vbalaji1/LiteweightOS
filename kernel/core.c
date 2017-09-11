#include "core.h"
#include "vga.h"


//http://wiki.osdev.org/Inline_Assembly/Examples
inline void outb(uint16_t port, uint8_t id) {
	asm volatile ("outb %0, %1" : : "a"(id), "Nd"(port));
}

//http://wiki.osdev.org/Inline_Assembly/Examples
inline uint8_t inb(uint16_t port) {
	uint8_t out;
	asm volatile ("inb %1, %0" : "=a"(out) : "Nd"(port));
	return out;
}

void xor_swap(char* a, char* b) {
	*a ^= *b;
	*b ^= *a;
	*a ^= *b;
}

size_t strlen(const char* str) {
	int len = 0;
	while (*str != '\0') {
		len++;
		str++;
	}
	return len;
}

void reverse(char* str) {
	char* end = str + strlen(str) - 1;
	while (end > str) {
		xor_swap(str, end);
		str++; end--;
	} 
}

char* itoa(int val) {
	char table[10] = "0123456789";
	static char result[64] = {0};
	int i = 0;
	bool negative = (val < 0) ? true : false;
	val = negative ? -val : val;
	if (val == 0) {
		result[0] = '0';
		result[1] = '\0';
		return result;
	}
	while (val) {
		result[i++] = table[val % 10];
		val /= 10;
	}
	if (negative) {
		result[i++] = '-';
	}
	result[i] = '\0';
	reverse(result);
	return result;
}

char* itoa_d(unsigned int val) {
	char table[10] = "0123456789";
	static char result[64] = {0};
	int i = 0;
	if (val == 0) {
		result[0] = '0';
		result[1] = '\0';
		return result;
	}
	while (val) {
		result[i++] = table[val % 10];
		val /= 10;
	}
	result[i] = '\0';
	reverse(result);
	return result;
}

char* itoa_hex(unsigned int val) {
	char table[16] = "0123456789abcdef";
	static char result[64] = {0};
	int i = 0;
	if (val == 0) {
		result[0] = '0';
		result[1] = '\0';
		return result;
	}
	while (val) {
		result[i++] = table[val % 16];
		val /= 16;
	}
	result[i++] = 'x';
	result[i++] = '0';
	result[i] = '\0';
	reverse(result);
	return result;
}

void* memset(void* s, int c, size_t n) {
	unsigned char* cpy = s;
	while (n > 0) {
		*cpy++ = (unsigned char) c;
		n--;
	}
	return s;
}
