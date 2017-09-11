MB_PAGE_ALIGN equ 1<<0
MB_MEMORY_MAP equ 1<<1
MB_FLAGS equ MB_PAGE_ALIGN | MB_MEMORY_MAP
MB_MAGIC_NUM equ 0x1BADB002 
MB_CHECKSUM equ -(MB_MAGIC_NUM + MB_FLAGS)
MB_STACK_SIZE equ 16384


section .multiboot
align 4
	dd MB_MAGIC_NUM
	dd MB_FLAGS
	dd MB_CHECKSUM

section .bss
align 16
stack_base_ptr:
	resb MB_STACK_SIZE

section .text

extern kernel_main
global _start

_start:
	mov esp, stack_base_ptr + MB_STACK_SIZE
	push ebx
	cli
	call kernel_main
	call halt

halt:
	hlt
	jmp halt 