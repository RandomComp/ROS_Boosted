#ifndef _RANDOM_OS_BUFFER_H
#define _RANDOM_OS_BUFFER_H

#include "core/basic_types.h"

#include "buffer/buffer_fwd.h"

#define MAGIC 0xBAF00000

bool Buffer_is_valid(const Buffer* buffer);
const c_str Buffer_why_invalid(const Buffer* buffer);
bool Buffer_checkForValidBuffer(const Buffer* buffer);

Buffer_ErrorCode Buffer_sendID(Buffer* this);
Buffer_ErrorCode Buffer_newID(Buffer* this);
Buffer_ErrorCode Buffer_freeID(Buffer* this);

Buffer_ErrorCode Buffer_wait_for_bytes(Buffer* this, Buffer_Port port);

Buffer_ErrorCode Buffer_resize(Buffer* this, size_t size, size_t context_size);
Buffer_ErrorCode Buffer_increase(Buffer* this, size_t size, size_t context_size);

uint32 Buffer_checksum_pack(byte ver, bool have_context, bool is_static, bool context_is_static);

Buffer_ErrorCode Buffer_checksum_unpack(uint32 checksum, byte* ver, bool* have_context, bool* is_static, bool* context_is_static);

bool Buffer_sig_check(const Buffer* buffer);

c_str Buffer_get_name(const Buffer* buffer);

ErrorCode Buffer_log(Buffer* buffer, LogSeverity severity, Buffer_ErrorCode code, const c_str msg, ...);

// Подписывает сигнатуру буфера, номер версии занимает полубайт
Buffer_ErrorCode Buffer_sign(Buffer* buffer, byte ver, const c_str name);

Buffer* Buffer_new(size_t size, size_t context_size, Buffer_CreationFlags flags);

Buffer_ErrorCode Buffer_last_err(Buffer* buffer, c_str* msg);

bool Buffer_is_active(Buffer* this);

const c_str Buffer_why_inactive(Buffer* this);

// API-обертка this->open
Buffer_ErrorCode Buffer_open(Buffer* this);

// Стандартные функции для любого Buffer
Buffer_ErrorCode Buffer_seek(Buffer* this, ssize_t bytes, Buffer_FlagsSeek flag);

Buffer_ErrorCode Buffer_write(Buffer* this, size_t start, 
							 const byte* data, size_t bytes, Buffer_Port port);
Buffer_ErrorCode Buffer_read(Buffer* this, size_t start, 
							byte* data, size_t bytes, Buffer_Port port);

Buffer_ErrorCode Buffer_write_byte(Buffer* this, byte data, Buffer_Port port);
Buffer_ErrorCode Buffer_read_byte(Buffer* this, byte* data, Buffer_Port port);

Buffer_ErrorCode Buffer_flush(Buffer* this, size_t bytes, Buffer_Port port);
Buffer_ErrorCode Buffer_fetch(Buffer* this, size_t bytes, Buffer_Port port);
Buffer_ErrorCode Buffer_fetch_count(Buffer* this, size_t* count, Buffer_Port port);

// API-обертка this->reset
Buffer_ErrorCode Buffer_reset(Buffer* this);
// API-обертка this->close
Buffer_ErrorCode Buffer_close(Buffer* this);
// API-обертка this->free
Buffer_ErrorCode Buffer_free(Buffer* this);

#endif