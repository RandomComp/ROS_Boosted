#include "drivers/multiboot/multiboot_types.h"

#include "std/std.h"

#include "drivers/hid/keyboardps2.h"

#include "drivers/acpi/acpi.h"

#include "drivers/memory/ram.h"

void main(uint32 magic, multibootInfo* info) {
	RAM_init(info);

	printf("RAM Size is: [value: size]", RAM_getSize());

	KeyboardPS2_Init();

	ACPI_Init();

	printf("OS is booted succesfully!\n");

	printf("Поклоняюсь Нейромонаху Феофану, Земфире, IOWA, ABBA, Adele, Alan Walker, AronChupa! Вдохновляясь их песнями, это ядро был создано!");

	for (;;);
}