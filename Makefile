SUBDIRS := kernel

.PHONY : all $(SUBDIRS)

all : kernel myos.iso 

$(SUBDIRS) :
	$(MAKE) -C $@ 

myos.iso: myos.bin
	grub-mkrescue -o myos.iso isodir 

myos.bin: kernel/boot.o kernel/kernel.o 
	i686-elf-gcc -T kernel/linker.ld -o myos.bin -ffreestanding -O2 -nostdlib kernel/boot.o kernel/kernel.o kernel/vga.o kernel/core.o kernel/gdt_flush.o kernel/tss_flush.o kernel/gdt.o kernel/mmap.o kernel/p_alloc.o -lgcc
	cp myos.bin isodir/boot/myos.bin


clean:
	rm kernel/boot.o kernel/kernel.o kernel/vga.o kernel/core.o kernel/gdt_flush.o kernel/tss_flush.o kernel/gdt.o kernel/mmap.o myos.bin