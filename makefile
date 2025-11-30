CFLAGS  = -m32 -fno-builtin -nostdinc -nostdlib

GASFLAGS = --32

OBJECT_FILES = ${shell find sources -type f -name "*.o" -printf "%p "}

all: clean gassources nasmsources $(OBJECT_FILES) kernel.bin image vmwareDisk

image:
	@echo "Creating hdd.img..."

	@echo "Copy kernel and grub files on partition..."

	@rm -f hdd.img

	@cp kernel.bin img/boot/
	
	@grub-mkrescue img/ -o hdd.img
	
	@echo "Done!"

	@make clean

run:
	@qemu-system-i386 -vga vmware -drive file=hdd.img,format=raw
flash:
	@sudo dd if=./hdd.img of=/dev/sdb

nasmsources:
	@nasm -f elf32 sources/gdt.n -o objectFiles/gdts.o

	@nasm -f elf32 sources/idt.n -o objectFiles/idts.o

gassources:
	@as $(GASFLAGS) -o objectFiles/loader.o loader.s

	@as $(GASFLAGS) -o objectFiles/mems.o sources/mem.s

	@as $(GASFLAGS) -o objectFiles/setjmp.o sources/setjmp.s

csources: $(OBJECT_FILES)
	@gcc -Iinclude $(CFLAGS) -o $@ -c $<

kernel.bin:
	@ld -m elf_i386 -T linker.ld -o $@ $^
vmwareDisk:
	@qemu-img convert -f raw hdd.img -O vmdk ./RandomOS.vmdk
clean:
	@rm -rf ${OBJECT_FILES}