#ifndef _RANDOM_OS_BUFFER_TYPES_H
#define _RANDOM_OS_BUFFER_TYPES_H

#include "core/basic_types.h"

#include "buffer/buffer_fwd.h"
#include "buffer/buffer_dest_fwd.h"

typedef enum Buffer_Controls {
	BUFFER_NEW_ID = 0xF1, // Комманда получения нового ID для буфера, регистрирует буфер у цели
	BUFFER_OPEN = 0xF0, // Комманда открытия буфера, сигнализирует о готовности получать и отправлять данные
	BUFFER_MESS_BEGIN = 0xDB, // Комманда начала сообщения
	BUFFER_MESS_SIZE_END = 0xDE, // Комманда конца размера сообщения
	BUFFER_CLOSE = 0xC0, // Комманда закрытия буфера, сигнализирует о прекращения отправки/получения данных
	BUFFER_FREE = 0xFF, // Комманда освобождения буфера, освобождает ID
} Buffer_Controls;

struct Buffer {
	byte sig[16]; // buff (4 байта), дальше байты checksum (занимает 4 байт), дальше название вида буфера (8 байт)

	byte* commands; size_t commands_size; // Управляющие байты и размер управляющих байт
	byte* data; size_t data_size; // Данные буфера и размер данных
	byte* context; size_t context_size; // Доп. данные и размер доп. данных
	
	bool is_static:1; 			// Флаг при фиксированном массиве data, 	влияет на checksum
	bool context_is_static:1; 	// Флаг при фиксированном массиве context, 	влияет на checksum

	bool is_open:1; 			// Флаг открытого буфера
	
	bool have_seek:1; 			// Флаг наличия функции seek, 	влияет на checksum

	word id; 					// ID буфера, 					влияет на checksum

	size_t updated_bytes; // Кол-во обновленных байт

	bool response_pending;

	ssize_t data_pos; // Позиция курсора в буфере для записи
	ssize_t load_pos; // Позиция курсора в буфере для flush

	ssize_t command_pos; // Позиция курсора в буфере для записи
	ssize_t command_load_pos; // Позиция курсора в буфере для flush

	size_t err_last, err_cnt;
	Buffer_ErrorCode* err; c_str* err_msg;

	BufferDest* dest;

	ErrorCode (*open)(Buffer* this); // Функция для открытия буфера, 	влияет на checksum

	// Функция для перехода курсора буфера (может быть недоступно в некоторых случаях)
	ErrorCode (*seek)(Buffer* this, ssize_t bytes, Buffer_FlagsSeek flag);

	// Вернуть буфер в начальное состояние
	ErrorCode (*reset)(Buffer* this);

	// Закрыть буфер, влияет на checksum
	ErrorCode (*close)(Buffer* this);
	
	// Освободить ресурсы буфера
	ErrorCode (*free)(Buffer* this);
};

#endif