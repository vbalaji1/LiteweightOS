all:
	nasm -felf boot.asm -o boot.o 
	nasm -felf gdt_flush.asm -o gdt_flush.o 
	nasm -felf tss_flush.asm -o tss_flush.o 
	i686-elf-gcc -c kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	i686-elf-gcc -c vga.c -o vga.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	i686-elf-gcc -c core.c -o core.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	i686-elf-gcc -c gdt.c -o gdt.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	i686-elf-gcc -c mmap.c -o mmap.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	i686-elf-gcc -c p_alloc.c -o p_alloc.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
