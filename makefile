CFLAGS  = -m32 -ffrestanding -fno-builtin -nostdinc -nostdlib

GASFLAGS = --32

C_FILES =			${shell find sources -type f -name "*.c" -printf "%p "}

GAS_FILES = 		${shell find sources -type f -name "*.s" -printf "%p "}

NASM_FILES =		${shell find sources -type f -name "*.n" -printf "%p "}

OBJECT_C_FILES = 	${C_FILES:.c=.o}

OBJECT_GAS_FILES = 	${C_FILES:.s=.o}

OBJECT_NASM_FILES = ${C_FILES:.n=.o}

all: clean $(OBJECT_C_FILES) $(OBJECT_GAS_FILES) $(OBJECT_NASM_FILES) kernel.bin image vmwareDisk

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

csources: $(OBJECT_C_FILES)
	@gcc -Iinclude $(CFLAGS) -o $@ -c $<

kernel.bin:
	@ld -m elf_i386 -T linker.ld -o $@ $^
vmwareDisk:
	@qemu-img convert -f raw hdd.img -O vmdk ./RandomOS.vmdk
clean:
	@rm -rf ${OBJECT_C_FILES} ${OBJECT_GAS_FILES} ${OBJECT_NASM_FILES}