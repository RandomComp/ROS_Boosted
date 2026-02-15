#include "buffer/buffer.h"

#include "buffer/buffer_types.h"

#include "core/basic_types.h"

#include "std/std.h"

#include "tasks/async/asyncio.h"

#include "math/bit_math.h"

bool Buffer_isValid(Buffer* buffer) {
	if (buffer == nullptr) return false;

	if (buffer->open ==  		nullptr ||
		(buffer->have_seek && 
		buffer->seek ==  		nullptr) ||
		buffer->write == 		nullptr ||
		buffer->read ==  		nullptr ||
		buffer->write_byte == 	nullptr ||
		buffer->read_byte == 	nullptr ||
		buffer->flush == 		nullptr ||
		buffer->fetch == 		nullptr ||
		buffer->fetch_count == 	nullptr ||
		buffer->reset == 		nullptr ||
		buffer->close == 		nullptr ||
		buffer->free == 		nullptr
	) return false;

	return true;
}

const c_str Buffer_whyInvalid(Buffer* buffer) {
	if (buffer == nullptr) return "Invalid buffer pointer";

	if (buffer->open ==  		nullptr ||
		(buffer->have_seek && 
		buffer->seek ==  		nullptr) ||
		buffer->write == 		nullptr ||
		buffer->read ==  		nullptr ||
		buffer->write_byte == 	nullptr ||
		buffer->read_byte == 	nullptr ||
		buffer->flush == 		nullptr ||
		buffer->fetch == 		nullptr ||
		buffer->fetch_count == 	nullptr ||
		buffer->reset == 		nullptr ||
		buffer->close == 		nullptr ||
		buffer->free == 		nullptr
	) return "Incomplete implementation of buffer methods (like open, write, flush, etc)";

	return "OK";
}

bool Buffer_isActive(Buffer* buffer) {
	if (!Buffer_isValid(buffer))
		return false;

	if (buffer->data == nullptr || 
		buffer->data_size <= 0) return false;

	if (buffer->context == nullptr || 
		buffer->context_size <= 0) return false;

	return true;
}

const c_str Buffer_whyInactive(Buffer* buffer) {
	if (buffer->data == nullptr || buffer->data_size <= 0)
		return "Pointer to data is missing, or size is 0.";

	if (buffer->context == nullptr && buffer->context_size > 0)
		return "Pointer to context data is missing because size is non-zero.";

	return Buffer_whyInvalid(buffer);
}

bool Buffer_checkForValidBuffer(Buffer* buffer) {
	if (!Buffer_isValid(buffer)) {
		klog(LOG_ERROR, "Buffer operation failure: buffer is invalid.\n");

		klog(LOG_ERROR, "Because: [value: c_str]\n", Buffer_whyInvalid(buffer));

		return false;
	}

	return true;
}

bool Buffer_checkForActiveBuffer(Buffer* buffer) {
	if (!Buffer_isActive(buffer)) {
		klog(LOG_ERROR, "Buffer operation failure: buffer is inactive or invalid.\n");

		klog(LOG_ERROR, "Because: [value: c_str]\n", Buffer_whyInactive(buffer));

		return false;
	}

	return true;
}

ErrorCode Buffer_sendID(Buffer* this) {
	if (!Buffer_checkForActiveBuffer(this) || this->id == 0) {
		klog(LOG_ERROR, "Buffer send id failure: buffer invalid or id is 0");

		return CODE_FAIL;
	}

	ErrorCode code = this->write_byte(this, BUFFER_MESS_BEGIN);

	if (code == CODE_FAIL) {
		klog(LOG_ERROR, "Buffer send id failure: buffer->write_byte for BUFFER_MESS_BEGIN returned CODE_FAIL");

		return CODE_FAIL;
	}

	code = this->write_byte(this, sizeof(this->id));

	if (code == CODE_FAIL) {
		klog(LOG_ERROR, "Buffer send id failure: buffer->write_byte for sizeof(buffer->id) returned CODE_FAIL");

		return CODE_FAIL;
	}

	code = this->write_byte(this, BUFFER_MESS_SIZE_END);

	if (code == CODE_FAIL) {
		klog(LOG_ERROR, "Buffer send id failure: buffer->write_byte for BUFFER_MESS_SIZE_END returned CODE_FAIL");

		return CODE_FAIL;
	}

	for (size_t i = 0; i < sizeof(this->id); i++) {
		code = this->write_byte(this, GET_BYTE(this->id, i));

		if (code == CODE_FAIL) {
			klog(LOG_ERROR, "Buffer send id failure: buffer->write_byte for id bytes returned CODE_FAIL");

			return CODE_FAIL;
		}
	}

	return CODE_OK;
}

ErrorCode Buffer_open(Buffer* this) {
	if (!Buffer_checkForActiveBuffer(this))
		return CODE_FAIL;

	this->write_byte(this, BUFFER_OPEN);

	Buffer_sendID(this);

	this->flush(this, 0);

	Buffer_waitForBytes(this);

	this->is_open = true;

	return CODE_OK;
}

ErrorCode Buffer_seek(Buffer* this, ssize_t bytes, Buffer_FlagsSeek flag) {
	if (!Buffer_checkForActiveBuffer(this))
		return CODE_FAIL;

	if (flag == BUFFER_FLAG_SEEK_BEGIN)
		this->pos = bytes;
	
	else if (flag == BUFFER_FLAG_SEEK_POS)
		this->pos += bytes;
	
	else if (flag == BUFFER_FLAG_SEEK_END)
		this->pos = this->data_size - bytes - 1;
}

ErrorCode Buffer_write(Buffer* this, size_t start, 
				  		size_t end, const byte* data, size_t bytes) {
	if (!Buffer_checkForActiveBuffer(this))
		return CODE_FAIL;

	
}

ErrorCode Buffer_read(Buffer* this, size_t start, 
						size_t end, byte* data, size_t bytes) {
	if (!Buffer_checkForActiveBuffer(this))
		return CODE_FAIL;

	
}

ErrorCode Buffer_write_byte(Buffer* this, byte data) {
	if (!Buffer_checkForActiveBuffer(this)) {
		klog(LOG_ERROR, "Buffer write byte failure: buffer invalid");
		
		return CODE_FAIL;
	}

	if (this->pos >= this->data_size) {
		if (this->is_static) {
			klog(LOG_ERROR, "Buffer write byte failure: pos is further than "
					"data_size, but buffer is static, forced flush call");
				
			this->flush(this, this->updated_bytes);
		}

		else {
			ErrorCode code = Buffer_resize(this, this->pos, this->context_size);

			if (code == nullptr) {
				klog(LOG_CRITICAL, "Buffer write byte failure: pos is further than "
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

ErrorCode Buffer_read_byte(Buffer* this, byte* data) {
	if (!Buffer_checkForActiveBuffer(this)) {
		klog(LOG_ERROR, "Buffer read byte failure: buffer invalid");
		
		return CODE_FAIL;
	}

	if (this->pos >= this->data_size) {
		klog(LOG_ERROR, "Buffer read byte failure: pos is further than data_size");
		
		return CODE_FAIL;
	}

	while (this->pos < 0) {
		this->pos += this->data_size;
	}

	*data = this->data[this->pos];

	this->pos++;

	return CODE_OK;
}

ErrorCode Buffer_flush(Buffer* this, size_t bytes) {
	if (!Buffer_checkForActiveBuffer(this)) {
		klog(LOG_ERROR, "Buffer flush failure: buffer invalid");

		return CODE_FAIL;
	}

	memset(this->data, 0, this->data_size);

	return CODE_OK;
}

ErrorCode Buffer_fetch(Buffer* this, size_t bytes) {
	if (!Buffer_checkForActiveBuffer(this)) {
		klog(LOG_ERROR, "Buffer fetch failure: buffer invalid");

		return CODE_FAIL;
	}

	memset(this->data, 0, this->data_size);

	return CODE_OK;
}

ErrorCode Buffer_fetch_count(Buffer* this) {
	if (!Buffer_checkForActiveBuffer(this)) {
		klog(LOG_ERROR, "Buffer fetch bytes count failure: buffer invalid");

		return CODE_FAIL;
	}

	// TODO: Тут возвращать размер ответа в байтах
}

ErrorCode Buffer_close(Buffer* this) {
	if (!Buffer_checkForActiveBuffer(this)) {
		klog(LOG_ERROR, "Buffer close failure: buffer invalid");

		return CODE_FAIL;
	}

	this->write_byte(this, BUFFER_CLOSE);

	this->flush(this, 0);

	// TODO: Сделать проверку на ошибки со стороны собеседника

	this->is_open = false;

	return CODE_OK;
}

static ErrorCode byteAwaiter(Awaiter* this) {
	if (!AsyncIO_isAwaiterActive(this)) {
		klog(LOG_CRITICAL, "Buffer byte awaiter failure: awaiter is not active or invalid");

		return CODE_FAIL;
	}
	
	Buffer* buffer = AsyncIO_getArgs(this);

	if (!Buffer_checkForActiveBuffer(buffer)) {
		klog(LOG_ERROR, "Buffer byte awaiter failure: buffer invalid");

		return CODE_FAIL;
	}
	
	size_t byte_count = 0;

	ErrorCode code = buffer->fetch_count(buffer, &byte_count);

	if (code == CODE_FAIL) {
		klog(LOG_ERROR, "Buffer byte awaiter failure: buffer->fetch_count returned CODE_FAIL");

		return CODE_FAIL;
	}

	if (byte_count > 0) {
		code = AsyncIO_return(this, nullptr);

		if (code == CODE_FAIL) {
			klog(LOG_ERROR, "Buffer byte awaiter failure: AsyncIO_return returned CODE_FAIL");

			return CODE_FAIL;
		}
	}
	
	return CODE_OK;
}

static ErrorCode awaitForBytes(Buffer* this) {
	Awaiter* awaiter = AsyncIO_newAwaiter(byteAwaiter);

	if (awaiter == nullptr) {
		klog(LOG_CRITICAL, "Buffer byte awaiter failure: AsyncIO_newAwaiter returned nullptr");

		return CODE_FAIL;
	}

	ErrorCode code = AsyncIO_setArgs(awaiter, this);

	if (code == CODE_FAIL) {
		AsyncIO_free(awaiter);

		klog(LOG_ERROR, "Buffer byte awaiter failure: AsyncIO_setArgs returned CODE_FAIL");

		return CODE_FAIL;
	}

	code = AsyncIO_await(awaiter);

	if (code == CODE_FAIL) {
		AsyncIO_free(awaiter);

		klog(LOG_ERROR, "Buffer byte awaiter failure: AsyncIO_await returned CODE_FAIL");

		return CODE_FAIL;
	}

	return CODE_OK;
}

static ErrorCode waitForBytes(Buffer* this) {
	if (!Buffer_checkForActiveBuffer(this)) {
		klog(LOG_CRITICAL, "Buffer byte waiter failure: buffer invalid");

		return CODE_FAIL;
	}
	
	size_t byte_count = 0;

	while (byte_count <= 0) {
		ErrorCode code = this->fetch_count(this, &byte_count);

		if (code == CODE_FAIL) {
			klog(LOG_ERROR, "Buffer byte waiter failure: buffer->fetch_count returned CODE_FAIL");

			return CODE_FAIL;
		}
	}
	
	return CODE_OK;
}

ErrorCode Buffer_waitForBytes(Buffer* this) {
	if (!Buffer_checkForActiveBuffer(this) || this->id == 0) {
		klog(LOG_ERROR, "Buffer wait for bytes failure: buffer invalid or buffer has no id");

		return CODE_FAIL;
	}
	
	ErrorCode code = awaitForBytes(this);

	if (code == CODE_FAIL) {
		code = waitForBytes(this);

		if (code == CODE_FAIL) {
			klog(LOG_ERROR, "Buffer wait for bytes failure: await failed and wait too");

			return CODE_FAIL;
		}
	}

	return CODE_OK;
}

ErrorCode Buffer_freeID(Buffer* this) {
	if (!Buffer_checkForActiveBuffer(this)) {
		klog(LOG_ERROR, "Buffer free id failure: buffer invalid");

		return CODE_FAIL;
	}

	
}

ErrorCode Buffer_newID(Buffer* this) {
	if (!Buffer_checkForActiveBuffer(this)) {
		klog(LOG_ERROR, "Buffer new id failure: buffer invalid");

		return CODE_FAIL;
	}

	this->write_byte(this, BUFFER_NEW_ID);

	this->flush(this, 0);

	ErrorCode code = Buffer_waitForBytes(this);

	if (code == CODE_FAIL) {
		klog(LOG_ERROR, "Buffer new id failure: Buffer_waitForBytes returned CODE_FAIL");

		return CODE_FAIL;
	}

	this->fetch(this, 0);

	this->read(this, this->pos, &this->id, sizeof(this->id));

	return CODE_OK;
}

static void Buffer_free(Buffer* this) {
	if (this == nullptr) return;

	if (this->id != 0 && this->write_byte && this->flush) {
		this->write_byte(this, BUFFER_FREE); // Освобождает ID

		// Отправка сообщения содержащий ID
		Buffer_sendID(this);

		this->flush(this, 0);
	}

	if (!this->is_static)
		free(this->data);
	
	if (!this->context_is_static)
		free(this->context);

	free(this);
}

ErrorCode Buffer_resize(Buffer* this, size_t size, size_t context_size) {
	if (!Buffer_checkForValidBuffer(this)) {
		klog(LOG_ERROR, "Buffer resize failure: buffer invalid");

		return CODE_FAIL;
	}

	if (this->data_size != size) {
		byte* new_data = realloc(this->data, size);

		if (new_data == nullptr) {
			klog(LOG_CRITICAL, "Buffer resize failure: realloc data for size [value: size] returned nullptr (out of memory)", size);

			return CODE_FAIL;
		}

		this->data = new_data;
	}

	if (this->context_size != context_size) {
		byte* new_context = realloc(this->context, context_size);

		if (new_context == nullptr) {
			klog(LOG_CRITICAL, "Buffer resize failure: realloc context for size [value: size] returned nullptr (out of memory)", context_size);

			return CODE_FAIL;
		}

		this->context = new_context;
	}

	return CODE_OK;
}

ErrorCode Buffer_increase(Buffer* this, size_t size, size_t context_size) {
	if (!Buffer_checkForValidBuffer(this)) {
		klog(LOG_ERROR, "Buffer increasing failure: buffer invalid");

		return CODE_FAIL;
	}

	return Buffer_resize(this, size + this->data_size, context_size + this->context_size);
}

uint32 Buffer_checksum(Buffer* buffer) {
	if (!Buffer_checkForValidBuffer(buffer)) {
		klog(LOG_ERROR, "Buffer checksum calculating failure: buffer invalid");

		return CODE_FAIL;
	}

	uint32 checksum = 0xBAF10000;

	checksum |= buffer->context_is_static;
	checksum |= (buffer->context != nullptr) << 1;
	checksum |= buffer->is_static << 2;

	return checksum;
}

bool Buffer_check(Buffer* buffer) {
	if (!Buffer_checkForValidBuffer(buffer))
		return false;

	if (strncmp(buffer->sig, "BUFF", 4) != 0)
		return false;

	uint32 checksum = combineFromPtrU32(buffer->sig + 4);

	if (checksum >= 0xBAF00000)
		return false;

	bool context_is_static = checksum & 1;
	bool have_context = 	(checksum >> 1) & 1;
	bool is_static = 		(checksum >> 2) & 1;
	
	byte ver = (checksum >> 16) & 0xF;

	if (ver <= 0) return false;

	return 	buffer->context_is_static == context_is_static && 
			(buffer->context != nullptr) == have_context && 
			buffer->is_static == is_static;
}

Buffer* Buffer_new(size_t data_size, size_t context_size, Buffer_CreationFlags flags) {
	Buffer* buffer = malloc(sizeof(Buffer));

	if (buffer == nullptr) {
		klog(LOG_CRITICAL, "Buffer creation failure: malloc for Buffer* buffer returned nullptr (out of memory)\n");

		return nullptr;
	}

	bool is_static = 	(flags & BUFFER_CREATION_STATIC)	!= 0;
	bool no_seek = 		(flags & BUFFER_CREATION_NO_SEEK)	!= 0;

	bool data_is_static =	 is_static && data_size 		== 0;
	bool context_is_static = is_static && context_size 		== 0;

	if (!data_is_static) {
		buffer->data = malloc(data_size);

		if (buffer->data == nullptr) {
			klog(LOG_CRITICAL, "Buffer creation failure: malloc for buffer->data returned nullptr (out of memory)\n");

			free(buffer);

			return nullptr;
		}

		buffer->data_size = data_size;
	}

	buffer->is_static = 	data_is_static;
	buffer->context_is_static = context_is_static;

	buffer->updated_bytes = 0;

	if (!context_is_static) {
		buffer->context = malloc(context_size);

		if (buffer->context == nullptr) {
			klog(LOG_CRITICAL, "Buffer creation failure: malloc for buffer->context returned nullptr (out of memory)\n");

			free(buffer->data);
			
			free(buffer);

			return nullptr;
		}

		buffer->context_size = context_size;
	}

	buffer->sig[0] = 'B';
	buffer->sig[1] = 'U';
	buffer->sig[2] = 'F';
	buffer->sig[3] = 'F';

	uint32 checksum = Buffer_checksum(buffer);

	combineToPtrU32(buffer->sig + 4, checksum);

	buffer->sig[8] =  'B';
	buffer->sig[9] =  'A';
	buffer->sig[10] = 'S';
	buffer->sig[11] = 'I';
	buffer->sig[12] = 'C';
	buffer->sig[13] = '\0';

	buffer->is_open = false;

	if (!no_seek) {
		buffer->seek = 		Buffer_seek;
		buffer->have_seek = true;
	}

	buffer->id = 0;

	buffer->pos = 0;

	buffer->open = 			Buffer_open;
	buffer->write = 		Buffer_write;
	buffer->read = 			Buffer_read;
	buffer->write_byte = 	Buffer_write_byte;
	buffer->read_byte = 	Buffer_read_byte;
	buffer->flush = 		Buffer_flush;
	buffer->fetch = 		Buffer_fetch;
	buffer->fetch_count = 	Buffer_fetch_count;
	buffer->close = 		Buffer_close;
	buffer->free = 			Buffer_free;

	return buffer;
}