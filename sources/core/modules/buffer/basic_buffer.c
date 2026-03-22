#include "buffer/basic_buffer.h"

#include "core/basic_types.h"

#include "buffer/buffer.h"

#include "buffer/buffer_types.h"

#include "std/std.h"

bool BasicBuffer_is_active(Buffer* this) {
	if (this == nullptr) return false;

	if (this->open ==  			nullptr ||
		(this->have_seek && 
		this->seek ==  			nullptr)||
		this->reset == 			nullptr ||
		this->close == 			nullptr ||
		this->free == 			nullptr
	) return false;

	if (this->data == nullptr || this->data_size <= 0)
		return false;

	return true;
}

const c_str BasicBuffer_why_inactive(Buffer* this) {
	if (this == nullptr) return "Invalid basic buffer pointer";

	if (this->open ==  			nullptr ||
		(this->have_seek && 
		this->seek ==  			nullptr) ||
		this->reset == 			nullptr ||
		this->close == 			nullptr ||
		this->free == 			nullptr
	) return "Incomplete implementation of basic buffer methods (like open, write, flush, etc)";

	if (this->data == nullptr || this->data_size <= 0)
		return "Data pointer is invalid or the data size is 0.";

	return "OK";
}

Buffer_ErrorCode BasicBuffer_open(Buffer* this) {
	if (!Buffer_checkForActiveBuffer(this))
		return CODE_FAIL;

	Buffer_write_command_byte(this, BUFFER_OPEN);

	Buffer_sendID(this);

	Buffer_flush_command(this, 0);

	Buffer_wait_for_command_bytes(this);

	this->is_open = true;

	return CODE_OK;
}

Buffer_ErrorCode BasicBuffer_seek(Buffer* this, ssize_t bytes, Buffer_FlagsSeek flag) {
	if (flag == BUFFER_FLAG_SEEK_BEGIN)
		this->pos = bytes;
	
	else if (flag == BUFFER_FLAG_SEEK_POS)
		this->pos += bytes;
	
	else if (flag == BUFFER_FLAG_SEEK_END)
		this->pos = this->data_size - bytes - 1;
}

Buffer_ErrorCode BasicBuffer_write(Buffer* this, size_t start, 
				  		size_t end, const byte* data, size_t bytes) {
	
}

Buffer_ErrorCode BasicBuffer_read(Buffer* this, size_t start, 
						size_t end, byte* data, size_t bytes) {
	
}

Buffer_ErrorCode BasicBuffer_write_byte(Buffer* this, byte data) {
	if (this->pos >= this->data_size) {
		if (this->is_static) {
			klog(LOG_ERROR, "Basic Buffer write byte failure: pos is further than "
					"data_size, but buffer is static, forced flush call");
				
			this->flush(this, this->updated_bytes);
		}

		else {
			Buffer_ErrorCode code = Buffer_resize(this, this->pos, this->context_size);

			if (code == nullptr) {
				klog(LOG_CRITICAL, "Basic Buffer write byte failure: pos is further than "
					"data_size, but Buffer_resize for increasing data size returned "
					"nullptr (out of memory), forced flush call");
			
				this->flush(this, this->updated_bytes);
			}
		}
	}

	while (this->pos < 0) {
		this->pos += this->data_size;
	}

	this->data[this->pos] = data;

	this->pos++;

	this->updated_bytes++;

	return CODE_OK;
}

Buffer_ErrorCode BasicBuffer_read_byte(Buffer* this, byte* data) {
	if (!Buffer_checkForActiveBuffer(this)) {
		klog(LOG_ERROR, "Basic Buffer read byte failure: buffer invalid");
		
		return CODE_FAIL;
	}

	if (this->pos >= this->data_size) {
		klog(LOG_ERROR, "Basic Buffer read byte failure: pos is further than data_size");
		
		return CODE_FAIL;
	}

	while (this->pos < 0) {
		this->pos += this->data_size;
	}

	*data = this->data[this->pos];

	this->pos++;

	return CODE_OK;
}

Buffer_ErrorCode BasicBuffer_flush(Buffer* this, size_t bytes) {
	if (!Buffer_checkForActiveBuffer(this)) {
		klog(LOG_ERROR, "Basic Buffer flush failure: buffer invalid");

		return CODE_FAIL;
	}

	memset(this->data, 0, this->data_size);

	return CODE_OK;
}

Buffer_ErrorCode BasicBuffer_fetch(Buffer* this, size_t bytes) {
	if (!Buffer_checkForActiveBuffer(this)) {
		klog(LOG_ERROR, "Basic Buffer fetch failure: buffer invalid");

		return CODE_FAIL;
	}

	memset(this->data, 0, this->data_size);

	return CODE_OK;
}

Buffer_ErrorCode BasicBuffer_fetch_count(Buffer* this) {
	if (!Buffer_checkForActiveBuffer(this)) {
		klog(LOG_ERROR, "Basic Buffer fetch bytes count failure: buffer invalid");

		return CODE_FAIL;
	}

	// TODO: Тут возвращать размер ответа в байтах
}

Buffer_ErrorCode BasicBuffer_reset(Buffer* this) {
	if (!Buffer_checkForActiveBuffer(this)) {
		klog(LOG_ERROR, "Basic Buffer reset count failure: buffer invalid");

		return CODE_FAIL;
	}

	
}

Buffer_ErrorCode BasicBuffer_close(Buffer* this) {
	if (!Buffer_checkForActiveBuffer(this)) {
		klog(LOG_ERROR, "Basic Buffer close failure: buffer invalid");

		return CODE_FAIL;
	}

	this->write_byte(this, BUFFER_CLOSE);

	this->flush(this, 0);

	// TODO: Сделать проверку на ошибки со стороны собеседника

	this->is_open = false;

	return CODE_OK;
}

static void BasicBuffer_free(Buffer* this) {
	if (this == nullptr) return;

	if (this->id != 0 && this->write_byte && this->flush) {
		Buffer_ErrorCode code = this->write_byte(this, BUFFER_FREE); // Освобождает ID

		if (code == CODE_OK) {
			// Отправка сообщения содержащий ID
			Buffer_sendID(this);

			this->flush(this, 0);
		}
	}

	if (!this->is_static)
		free(this->data);
	
	if (!this->context_is_static)
		free(this->context);

	free(this);
}

Buffer* BasicBuffer_new(size_t size) {
	Buffer* buffer = Buffer_new(size, 0, 0);

	buffer->open = 			BasicBuffer_open;
	buffer->seek = 			BasicBuffer_seek;
	buffer->write = 		BasicBuffer_write;
	buffer->read = 			BasicBuffer_read;
	buffer->write_byte = 	BasicBuffer_write_byte;
	buffer->read_byte = 	BasicBuffer_read_byte;
	buffer->flush = 		BasicBuffer_flush;
	buffer->fetch = 		BasicBuffer_fetch;
	buffer->fetch_count = 	BasicBuffer_fetch_count;
	buffer->reset = 		BasicBuffer_reset;
	buffer->close = 		BasicBuffer_close;
	buffer->free = 			BasicBuffer_free;
}