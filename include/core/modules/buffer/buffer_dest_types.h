#ifndef _RANDOM_OS_BUFFER_DEST_TYPES_H
#define _RANDOM_OS_BUFFER_DEST_TYPES_H

#include "core/basic_types.h"

#include "buffer/buffer_fwd.h"

#include "buffer/buffer_dest_fwd.h"

struct BufferDest {
	byte sig[32]; // buffdest (8 байта), дальше байты checksum (занимает 8 байт), дальше название вида буфера (16 байт)

	byte* commands; size_t commands_size; // Управляющие байты и размер управляющих байт
	byte* data; size_t data_size; // Данные буфера и размер данных
	
	bool is_static:1; 			// Флаг при фиксированном массиве data, 	влияет на checksum
	
	word* ids; 					// Массив ID буферов, 						влияет на checksum

	size_t updated_bytes; // Кол-во обновленных байт

	bool response_pending;

	ssize_t write_pos; // Позиция курсора в буфере для записи
	ssize_t flush_pos; // Позиция курсора в буфере для flush

	size_t err_last, err_cnt;
	Buffer_ErrorCode* err; c_str* err_msg;

	// Функция для валидации буфера (не включает проверку сигнатуры), влияет на checksum
	bool (*is_active)(Buffer* this);
	
	// Функция для получения пояснения почему буфер некорректен (не включает проверку сигнатуры), влияет на checksum
	c_str (*why_inactive)(Buffer* this);
	
	// Функция для записи массива байтов в внутреннию память (работает как flush если буфер не имеет внутренней памяти)
	// При end = 0, end установливается в размер буфера
	ErrorCode (*write)(Buffer* this, size_t start, 
							 const byte* data, size_t bytes);

	ErrorCode (*read)(Buffer* this, size_t start, 
							byte* data, size_t bytes);

	// Функция для записи одного байта в внутреннию память буфера в позицию курсорра
	ErrorCode (*write_byte)(Buffer* this, byte data);
	// Функция для чтения одного байта из внутренней память буфера где курсор
	ErrorCode (*read_byte)(Buffer* this, byte* data);

	// При bytes = 0, bytes установливается в размер буфера, влияет на checksum
	ErrorCode (*flush)(Buffer* this, size_t bytes);
	// При bytes = 0, bytes установливается в размер буфера, влияет на checksum
	ErrorCode (*fetch)(Buffer* this, size_t bytes);

	// Получить кол-во обновленных байтов
	ErrorCode (*fetch_count)(Buffer* this, size_t* count);

	// Вернуть буфер в начальное состояние
	ErrorCode (*reset)(Buffer* this);
	
	// Освободить ресурсы буфера
	ErrorCode (*free)(Buffer* this);
};

#endif