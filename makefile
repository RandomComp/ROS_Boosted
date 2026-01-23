CFLAGS  = -Iinclude -Iinclude/core/modules -m32 -ffreestanding

GASFLAGS = --32

C_FILES :=				${shell find sources -type f -name "*.c" -printf "%p "}

GAS_FILES := 			${shell find sources -type f -name "*.s" -printf "%p "}

NASM_FILES :=			${shell find sources -type f -name "*.n" -printf "%p "}

OBJECT_C_FILES := 		${C_FILES:.c=.o}

OBJECT_GAS_FILES := 	${GAS_FILES:.s=.o}

OBJECT_NASM_FILES := 	${NASM_FILES:.n=.o}

all: clean $(OBJECT_C_FILES) $(OBJECT_GAS_FILES) $(OBJECT_NASM_FILES) kernel.bin image vmwareDisk

restore:
	@echo "Restore in progress..."

	@cp ${shell find ../RandomOS_Boosted_Backup/* -type f -name "*.c" -printf "%p "}

	@echo "Restore done!"

backup:
	@echo "Backup in progress..."

	@rm -rf ../RandomOS_Boosted_Backup

	@cp -r ../RandomOS_Boosted ../RandomOS_Boosted_Backup

	@echo "Backup done!"

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

%.o: %.n
	@nasm -f elf32 $< -o $@

%.o: %.s
	@as $(GASFLAGS) -o $@ $<

%.o: %.c
	@gcc $(CFLAGS) -o $@ -c $<

kernel.bin:
	@ld -m elf_i386 -T linker.ld -o $@ $^
vmwareDisk:
	@qemu-img convert -f raw hdd.img -O vmdk ./RandomOS.vmdk
clean:
	@echo ${OBJECT_C_FILES} ${OBJECT_GAS_FILES} ${OBJECT_NASM_FILES}
#	@rm -rf ${OBJECT_C_FILES} ${OBJECT_GAS_FILES} ${OBJECT_NASM_FILES}