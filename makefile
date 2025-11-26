CFLAGS  = -m32 -fpermissive -fno-builtin -nostdinc -nostdlib

GASFLAGS = --32

all: clean gassources nasmsources $(OBJFILES) kernel.bin image vmwareDisk

image:
	@echo "Creating hdd.img..."

	@echo "Copy kernel and grub files on partition..."

	@cp kernel.bin img/boot/

	@rm -f hdd.img
	
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

csources: $(OBJFILES)
#	@rm -f objectFiles/*.o

#	@mv -f sources/*.o objectFiles/
	
	@for file in *.img; do \
		echo "$${file%.img}"; \
	done

#	@gcc -Iinclude $(CFLAGS) -o $@ -c $<

kernel.bin: $(OBJFILES)
	@ld -m elf_i386 -T linker.ld -o $@ $^
vmwareDisk:
	@qemu-img convert -f raw hdd.img -O vmdk ./RandomOS.vmdk
clean:
	@rm -rf objectFiles