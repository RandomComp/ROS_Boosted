CFLAGS  = -m32 -fpermissive -fno-builtin -nostdinc -nostdlib

GASFLAGS = --32

OBJFILES = \
	loader.o  \
	sources/std.o  \
	sources/pci.o  \
	sources/bios.o  \
	sources/vbe.o  \
	sources/warning.o  \
	sources/fatal_error.o  \
	sources/error.o  \
	sources/mems.o \
	sources/mem.o \
	sources/speaker.o \
	sources/power.o \
	sources/acpi.o \
	sources/io.o  \
	sources/gdt.o  \
	sources/gdts.o  \
	sources/idt.o  \
	sources/idts.o  \
	sources/pit.o  \
	sources/keyboardps2.o  \
	sources/format.o  \
	sources/time.o  \
	sources/pci_driver.o \
	sources/colors.o \
	sources/glyph.o \
	sources/ugsm.o \
	sources/ascii.o \
	sources/rus.o \
	sources/qdivrem.o  \
	sources/udivdi3.o  \
	sources/umoddi3.o  \
	sources/divdi3.o  \
	sources/moddi3.o  \
	sources/x86emu.o  \
	sources/x86emu_util.o  \
	sources/setjmp.o  \
	sources/math.o  \
	sources/abc.o  \
	sources/archive.o  \
	sources/RL/lexer.o  \
	sources/RMAL/lexer.o  \
	sources/RMAL/parser.o  \
	kernel.o

all: clean gassources nasmsources $(OBJFILES) kernel.bin image vmwareDisk

image:
	@echo "Creating hdd.img..."

	@echo "Copy kernel and grub files on partition..."

	@cp kernel.bin img/boot/

	@rm -rf hdd.img
	
	@grub-mkrescue img/ -o hdd.img
	
	@echo "Done!"

	@make clean

run:
	@qemu-system-i386 -vga vmware -drive file=hdd.img,format=raw
flash:
	@sudo dd if=./hdd.img of=/dev/sdb

nasmsources:
	@nasm -f elf32 sources/gdt.n -o sources/gdts.o

	@nasm -f elf32 sources/idt.n -o sources/idts.o

gassources:
	@as $(GASFLAGS) -o loader.o loader.s

	@as $(GASFLAGS) -o sources/mems.o sources/mem.s

	@as $(GASFLAGS) -o sources/setjmp.o sources/setjmp.s

csources: $(OBJFILES)

%.o: %.c
	@g++ -Iinclude $(CFLAGS) -o $@ -c $<

kernel.bin: $(OBJFILES)
	@ld -m elf_i386 -T linker.ld -o $@ $^
vmwareDisk:
	@qemu-img convert -f raw hdd.img -O vmdk ./RandomOS.vmdk
clean:
	@rm -f $(OBJFILES) kernel.bin