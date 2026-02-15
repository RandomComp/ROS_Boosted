#ifndef _RANDOM_OS_BUFFER_TYPES_H
#define _RANDOM_OS_BUFFER_TYPES_H

#include "core/basic_types.h"

#include "buffer/buffer_fwd.h"

#define STATIC_BUF_SIZE 4096 // 4 КБ

typedef enum Buffer_Controls {
	BUFFER_NEW_ID = 0x10, // Комманда получения нового ID для буфера, регистрирует буфер у цели
	BUFFER_OPEN = 0xF0, // Комманда открытия буфера, сигнализирует о готовности получать и отправлять данные
	BUFFER_MESS_BEGIN = 0xD0, // Комманда начала сообщения
	BUFFER_MESS_SIZE_END = 0xD5, // Комманда конца размера
	BUFFER_CLOSE = 0xC0, // Комманда закрытия буфера, сигнализирует о прекращения отправки/получения данных
	BUFFER_FREE = 0xFF, // Комманда освобождения буфера, освобождает ID
} Buffer_Controls;

struct Buffer {
	byte sig[16]; // buff (4 байта), дальше байты checksum (занимает 4 байт), дальше название вида буфера (8 байт)

	byte* data; size_t data_size; // Данные буфера и размер данных
	
	byte* context; size_t context_size; // Доп. данные и размер доп. данных
	
	bool is_static:1; 			// Флаг при фиксированном массиве data, 	влияет на checksum
	bool context_is_static:1; 	// Флаг при фиксированном массиве context, 	влияет на checksum

	bool is_open:1; // Флаг открытого буфера
	
	bool have_seek:1; 	// Флаг наличия функции seek, 	влияет на checksum

	word id; 			// ID буфера, 					влияет на checksum

	size_t updated_bytes; // Кол-во обновленных байт

	ssize_t pos; // Позиция курсора в буфере

	const ErrorCode (*open)(Buffer* this); // Функция для открытия буфера, 					влияет на checksum

	// Функция для перехода курсора буфера (может быть недоступно в некоторых случаях)
	const ErrorCode (*seek)(Buffer* this, ssize_t bytes, Buffer_FlagsSeek flag);

	// Функция для записи массива байтов в внутреннию память (работает как flush если буфер не имеет внутренней памяти)
	// При end = 0, end установливается в размер буфера
	const ErrorCode (*write)(Buffer* this, size_t start, 
							 const byte* data, size_t bytes);

	const ErrorCode (*read)(Buffer* this, size_t start, 
							byte* data, size_t bytes);

	// Функция для записи одного байта в внутреннию память буфера в позицию курсорра
	const ErrorCode (*write_byte)(Buffer* this, byte data);
	// Функция для чтения одного байта из внутренней память буфера где курсор
	const ErrorCode (*read_byte)(Buffer* this, byte* data);

	// При bytes = 0, bytes установливается в размер буфера, влияет на checksum
	const ErrorCode (*flush)(Buffer* this, size_t bytes);
	// При bytes = 0, bytes установливается в размер буфера, влияет на checksum
	const ErrorCode (*fetch)(Buffer* this, size_t bytes);

	// Получить кол-во обновленных байтов
	const ErrorCode (*fetch_count)(Buffer* this, size_t* count);

	// Вернуть буфер в начальное состояние
	const ErrorCode (*reset)(Buffer* this);

	// Закрыть буфер, влияет на checksum
	const ErrorCode (*close)(Buffer* this);
	
	// Освободить ресурсы буфера
	const ErrorCode (*free)(Buffer* this);
};

#endif