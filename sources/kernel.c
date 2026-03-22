#include "drivers/multiboot/multiboot_types.h"

#include "std/std.h"

#include "drivers/hid/keyboardps2.h"

#include "drivers/acpi/acpi.h"

#include "drivers/memory/ram.h"

#include "buffer/basic_buffer.h"

void main(uint32 magic, multibootInfo* info) {
	RAM_init(info);

	printf("RAM Size is: [value: size]", RAM_getSize());

	KeyboardPS2_Init();

	ACPI_Init();

	printf("OS is booted succesfully!\n");

	printf("Поклоняюсь Нейромонаху Феофану, Земфире, IOWA, ABBA, Adele, Alan Walker, AronChupa! Вдохновляясь их песнями, это ядро был создано!");

	const c_str hello_str = "Hello, world!";

	Buffer* buffer = BasicBuffer_new(100);

	Buffer_write(buffer, 0, hello_str, strlen(hello_str), 0); // Пишем "Hello, world!" строкув buffer начиная с 0, порт оставляем стандартным
	
	c_str str = malloc(strlen(hello_str)); // Выделяем память
	
	Buffer_read(buffer, 0, str, 0, 0); // Читаем данные с стандартного порта, вместо размера данных 0 подставляется кол-во доступных для чтения байт

	printf(str); // Выводим получившиюся строку

	Buffer_reset(buffer); // Сбрасываем буфер

	Buffer_free(buffer); // Освобождаем буфер

	for (;;);
}