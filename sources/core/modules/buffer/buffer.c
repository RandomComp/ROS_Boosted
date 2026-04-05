#include "buffer/buffer.h"

#include "buffer/buffer_types.h"

#include "core/basic_types.h"

#include "std/std.h"

#include "tasks/async/asyncio.h"

#include "math/bit_math.h"

#include "std/string/format.h"

bool Buffer_is_valid(const Buffer* buffer) {
	if (buffer == nullptr)
		return false;
	
	if (buffer->open ==  		nullptr ||
		(buffer->have_seek && 
		buffer->seek ==  		nullptr)||
		buffer->close == 		nullptr ||
		buffer->free == 		nullptr
	) return false;

	if (buffer->commands == nullptr || 
		buffer->commands_size <= 0) return false;

	if (buffer->data == nullptr || 
		buffer->data_size <= 0) return false;

	if ((buffer->context == nullptr && 
		buffer->context_size > 0) || 
		(buffer->context != nullptr &&
		 buffer->context_size <= 0)) return false;

	return true;
}

const c_str Buffer_why_invalid(const Buffer* buffer) {
	if (buffer == nullptr)
		return "Buffer pointer is nullptr.";

	if (buffer->commands == nullptr)
		return "Pointer to command bytes is nullptr.";
	
	if (buffer->commands_size <= 0)
		return "Command size <= 0.";

	if (buffer->data == nullptr || buffer->data_size <= 0)
		return "Pointer to data is nullptr, or size is 0.";

	if ((buffer->context == nullptr && 
		buffer->context_size > 0))
		return "Pointer to context data is missing, because size > 0.";
	
	if ((buffer->context != nullptr &&
		 buffer->context_size <= 0))
		return "Pointer to context data exists, but size <= 0.";

	return "OK.";
}

bool Buffer_checkForValidBuffer(const Buffer* buffer) {
	if (!Buffer_is_valid(buffer)) {
		Buffer_log(buffer, LOG_ERROR, BUFFER_IS_INVALID_ERROR, 
					"Buffer operation failure: buffer is invalid.\n"
					"Because: [value: c_str]", Buffer_why_invalid(buffer));

		return false;
	}

	return true;
}

Buffer_ErrorCode Buffer_sendID(Buffer* this) {
	if (!Buffer_checkForValidBuffer(this) || this->id == 0) {
		klog(LOG_ERROR, "Buffer send id failure: buffer invalid or id is 0");

		return CODE_FAIL;
	}

	Buffer_write_byte(this, BUFFER_MESS_BEGIN, BUFFER_PORT_COMMAND);

	Buffer_write_byte(this, sizeof(this->id), BUFFER_PORT_COMMAND);

	Buffer_ErrorCode code = Buffer_write_byte(this, BUFFER_MESS_SIZE_END, BUFFER_PORT_COMMAND);

	for (size_t i = 0; i < sizeof(this->id); i++) {
		code = Buffer_write_byte(this, GET_BYTE(this->id, i), BUFFER_PORT_COMMAND);

		if (code != CODE_OK) {
			klog(LOG_ERROR, "Buffer send id failure: buffer->write_byte returned CODE_FAIL");

			break;
		}
	}

	return code;
}

static ErrorCode byteAwaiter(Awaiter* this) {
	if (!AsyncIO_is_awaiter_active(this)) {
		klog(LOG_CRITICAL, "Buffer byte awaiter failure: awaiter is not active or invalid");

		return CODE_FAIL;
	}

	if (!AsyncIO_any_arg(this)) {
		klog(LOG_ERROR, "Buffer byte awaiter failure: not buffer and port in arguments");

		return CODE_FAIL;
	}
	
	Buffer* buffer = AsyncIO_get_arg(this, 0);
	
	Buffer_Port* port = (Buffer_Port*)AsyncIO_get_arg(this, 1);

	if (!Buffer_checkForValidBuffer(buffer)) {
		Buffer_log(buffer, LOG_ERROR, BUFFER_WAIT_BYTES_ERROR, 
			"Buffer byte awaiter failure: buffer invalid"
		);

		return CODE_FAIL;
	}
	
	size_t byte_count = 0;

	Buffer_ErrorCode code = Buffer_fetch_count(buffer, &byte_count, *port);

	if (code != CODE_OK) {
		Buffer_log(buffer, LOG_ERROR, BUFFER_WAIT_BYTES_ERROR, 
			"Buffer byte awaiter failure: Buffer_fetch_count returned CODE_FAIL"
		);

		return CODE_FAIL;
	}

	if (byte_count > 0) {
		code = AsyncIO_return(this, nullptr);

		if (code != CODE_OK) {
			Buffer_log(buffer, LOG_ERROR, BUFFER_WAIT_BYTES_ERROR, 
				"Buffer byte awaiter failure: AsyncIO_return returned CODE_FAIL"
			);

			return CODE_FAIL;
		}
	}
	
	return CODE_OK;
}

static ErrorCode awaitBytes(Buffer* this, Buffer_Port* port_ptr) {
	Awaiter* awaiter = AsyncIO_newAwaiter(byteAwaiter);

	if (awaiter == nullptr) {
		klog(LOG_CRITICAL, "Buffer byte awaiter failure: AsyncIO_newAwaiter returned nullptr");

		return CODE_FAIL;
	}

	ErrorCode code = AsyncIO_set_arg(awaiter, 0, this);

	code = code || AsyncIO_set_arg(awaiter, 1, port_ptr);

	if (code != CODE_OK) {
		AsyncIO_free(awaiter);

		Buffer_log(this, LOG_ERROR, BUFFER_WAIT_BYTES_ERROR, 
			"Buffer byte awaiter failure: AsyncIO_set_arg returned CODE_FAIL"
		);

		return CODE_FAIL;
	}

	code = AsyncIO_await(awaiter);

	if (code != CODE_OK) {
		Buffer_log(this, LOG_ERROR, BUFFER_WAIT_BYTES_ERROR, 
			"Buffer byte awaiter failure: AsyncIO_await returned CODE_FAIL"
		);
	}
	
	AsyncIO_free(awaiter);

	return code;
}

static Buffer_ErrorCode waitBytes(Buffer* this, Buffer_Port* port_ptr) {
	if (!Buffer_checkForValidBuffer(this)) {
		Buffer_log(this, LOG_CRITICAL, BUFFER_WAIT_BYTES_ERROR, 
			"Buffer byte waiter failure: buffer invalid"
		);

		return CODE_FAIL;
	}
	
	size_t byte_count = 0;

	while (byte_count <= 0) {
		Buffer_ErrorCode code = Buffer_fetch_count(this, &byte_count, *port_ptr);

		if (code != CODE_OK) {
			klog(LOG_ERROR, "Buffer byte waiter failure: buffer->fetch_count returned CODE_FAIL");

			return CODE_FAIL;
		}
	}
	
	return CODE_OK;
}

Buffer_ErrorCode Buffer_wait_for_bytes(Buffer* this, Buffer_Port _port) {
	if (!Buffer_checkForValidBuffer(this) || this->id == 0) {
		Buffer_log(this, LOG_ERROR, BUFFER_WAIT_BYTES_ERROR, 
			"Buffer wait for bytes failure: buffer invalid or buffer has no id"
		);

		return CODE_FAIL;
	}

	Buffer_Port* port = malloc(sizeof(_port));

	*port = _port;
	
	Buffer_ErrorCode code = awaitBytes(this, port);

	if (code != CODE_OK)
		code = waitBytes(this, port);

	if (code != CODE_OK) {
		klog(LOG_ERROR, "Buffer wait for bytes failure: await and wait failed");
	}
	
	free(port);

	return code;
}

Buffer_ErrorCode Buffer_freeID(Buffer* this) {
	if (!Buffer_checkForValidBuffer(this)) {
		klog(LOG_ERROR, "Buffer free id failure: buffer invalid");

		return CODE_FAIL;
	}

	
}

Buffer_ErrorCode Buffer_newID(Buffer* this) {
	if (!Buffer_checkForValidBuffer(this)) {
		klog(LOG_ERROR, "Buffer new id failure: buffer invalid");

		return CODE_FAIL;
	}

	Buffer_write_byte(this, BUFFER_NEW_ID, BUFFER_PORT_COMMAND);

	Buffer_flush(this, 0, BUFFER_PORT_COMMAND);

	Buffer_wait_for_bytes(this, BUFFER_PORT_COMMAND);

	Buffer_fetch(this, 0, BUFFER_PORT_COMMAND);

	Buffer_ErrorCode code = Buffer_read(this, this->command_pos, &this->id, sizeof(this->id), BUFFER_PORT_COMMAND);

	if (code != CODE_OK) {
		
	}

	return code;
}

Buffer_ErrorCode Buffer_resize(Buffer* this, size_t size, size_t context_size) {
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

Buffer_ErrorCode Buffer_increase(Buffer* this, size_t size, size_t context_size) {
	if (!Buffer_checkForValidBuffer(this)) {
		klog(LOG_ERROR, "Buffer increasing failure: buffer invalid");

		return CODE_FAIL;
	}

	return Buffer_resize(this, size + this->data_size, context_size + this->context_size);
}

uint32 Buffer_checksum_pack(byte ver, bool have_context, bool is_static, bool context_is_static) {
	if (ver <= 0) {
		klog(LOG_ERROR, "Buffer checksum calculating failure: invalid version [value: u8], version can't be <= 0", ver);

		return 0;
	}

	uint32 checksum = MAGIC;

	checksum |= 1 << 16;
	
	checksum |= have_context;
	checksum |= is_static << 1;
	checksum |= context_is_static << 2;

	// TODO: реализовать упаковку в checksum типа реализации is_valid, why_invalid, open, flush, fetch, fetch_count, close

	return checksum;
}

ErrorCode Buffer_checksum_unpack(uint32 checksum, byte* ver, bool* have_context, bool* is_static, bool* context_is_static) {
	if (checksum <= MAGIC) {
		klog(LOG_ERROR, "Buffer checksum unpack failure: invalid checksum [value: h32]", checksum);

		return CODE_FAIL;
	}

	// TODO: реализовать распаковку в checksum типа реализации is_valid, why_invalid, open, flush, fetch, fetch_count, close

	return CODE_OK;
}

uint32 Buffer_checksum(const Buffer* buffer) {
	if (!Buffer_is_active(buffer)) {
		klog(LOG_ERROR, "Buffer checksum calculating failure: buffer invalid");

		return 0;
	}

	uint32 checksum = MAGIC;

	checksum |= 1 << 16;

	checksum |= buffer->context_is_static;
	checksum |= (buffer->context != nullptr) << 1;
	checksum |= buffer->is_static << 2;

	// TODO: реализовать упаковку в checksum типа реализации is_valid, why_invalid, open, flush, fetch, fetch_count, close

	return checksum;
}

bool Buffer_sig_check(const Buffer* buffer) {
	if (buffer == nullptr)
		return false;

	if (strncmp(buffer->sig, "BUFF", 4) != 0) // Проверяем заголовочный текст
		return false;

	uint32* checksum = buffer->sig + 4;

	if (*checksum >= 0xBAF00000) // Отбрасываем некорректные checksum
		return false;

	bool context_is_static = *checksum & 1;
	bool have_context = 	(*checksum >> 1) & 1;
	bool is_static = 		(*checksum >> 2) & 1;
	
	byte ver = (*checksum >> 16) & 0xF;

	if (ver <= 0) return false;

	return 	buffer->context_is_static == context_is_static && 
			(buffer->context != nullptr) == have_context && 
			buffer->is_static == is_static;
}

c_str Buffer_get_name(const Buffer* buffer) {
	if (Buffer_sig_check(buffer)) {
		klog(LOG_ERROR, "Buffer getting name failure: Buffer is invalid");

		return CODE_FAIL;
	}

	return buffer->sig + 8;
}

static const c_str severity_names[] = {
	[LOG_INFO] = 		"[INFO]",
	[LOG_WARNING] = 	"[WARN]",
	[LOG_ERROR] = 		"[ERROR]",
	[LOG_CRITICAL] = 	"[FATAL]"
};
	
static const c_str function_names[] = {
	[BUFFER_IS_ACTIVE_ERROR] 	= "is_active",
	[BUFFER_WHY_INACTIVE_ERROR] = "why_inactive",
	[BUFFER_OPEN_ERROR]		 	= "open",
	[BUFFER_SEEK_ERROR]		 	= "seek",
	[BUFFER_WRITE_ERROR]		= "write",
	[BUFFER_READ_ERROR]		 	= "read",
	[BUFFER_WRITE_BYTE_ERROR]	= "write_byte",
	[BUFFER_READ_BYTE_ERROR]	= "read_byte",
	[BUFFER_FLUSH_ERROR]		= "flush",
	[BUFFER_FETCH_ERROR]		= "fetch",
	[BUFFER_FETCH_COUNT_ERROR] 	= "fetch_count",
	[BUFFER_RESET_ERROR]		= "reset",
	[BUFFER_CLOSE_ERROR]		= "close",
	[BUFFER_FREE_ERROR]		 	= "free"
};

ErrorCode Buffer_log(Buffer* buffer, LogSeverity severity, Buffer_ErrorCode code, const c_str _msg, ...) {
	c_str severity_name = severity_names[severity];
	c_str function_name = function_names[code];
	c_str buffer_name = Buffer_get_name(buffer);

	c_str unknown = "unknown";

	if (severity_name == nullptr)
		severity_name = unknown;
	if (function_name == nullptr)
		function_name = unknown;
	if (buffer_name == nullptr)
		buffer_name = unknown;

	c_str msg = _msg != nullptr ? _msg : "message not provided.";
	
	c_str err_msg = Format_c_str("\\[[value: c_str]\\] [value: c_str]Buffer_[value: c_str] failed: [value: c_str]", 
								severity_name, buffer_name, function_name, msg);
	
	if (buffer == nullptr) {
		klog(LOG_ERROR, "Buffer log failure: Buffer is nullptr");

		kmsg(err_msg);

		return CODE_FAIL;
	}

	if (buffer->err_last >= buffer->err_cnt) {
		size_t new_size = buffer->err_last + 10;

		Buffer_ErrorCode* new_err = malloc(new_size * sizeof(Buffer_ErrorCode));

		if (new_err != nullptr) {
			c_str* new_err_msg = malloc(new_size * sizeof(c_str));

			if (new_err_msg != nullptr) {
				memcpy(new_err, 	buffer->err, 	 buffer->err_cnt * sizeof(Buffer_ErrorCode));
				memcpy(new_err_msg, buffer->err_msg, buffer->err_cnt * sizeof(c_str));

				free(buffer->err);
				free(buffer->err_msg);

				buffer->err = new_err;
				buffer->err_msg = new_err_msg;
				buffer->err_cnt = new_size;
			}

			else {
				free(new_err); new_err = nullptr;
			}
		}

		if (new_err == nullptr) {
			klog(LOG_CRITICAL, "Buffer log failure: realloc returned nullptr for buffer->err or buffer->err_msg (out of memory)");
		}
	}
	
	else {
		buffer->err[buffer->err_last] = code;
		buffer->err_msg[buffer->err_last] = err_msg;
	}

	kmsg(err_msg);

	return CODE_OK;
}

Buffer_ErrorCode Buffer_sign(Buffer* buffer, byte ver, const c_str name) {
	if (buffer == nullptr) {
		klog(LOG_ERROR, "Buffer sign failure: Buffer is nullptr\n");

		return BUFFER_SIGN_ERROR;
	}

	if (ver <= 0) {
		Buffer_log(buffer, LOG_ERROR, BUFFER_SIGN_ERROR, "invalid version [value: u8]\n", ver);

		return BUFFER_SIGN_ERROR;
	}

	memcpy(buffer->sig, "BUFF", 4);

	uint32* checksum = buffer->sig + 4;

	*checksum = Buffer_checksum(buffer);

	c_str buffer_name = buffer->sig + 8;

	for (size_t i = 0; i < 8 && name[i]; i++)
		buffer_name[i] = name[i];

	return CODE_OK;
}

Buffer_ErrorCode Buffer_last_err(Buffer* buffer, c_str* msg) {
	if (buffer == nullptr) {
		klog(LOG_ERROR, "Buffer last error getting failure: buffer is nullptr");

		return CODE_FAIL;
	}

	Buffer_ErrorCode code = CODE_FAIL;

	if (buffer->err_cnt >= 1) {
		size_t last = buffer->err_cnt - 1;

		if (buffer->err)
			code = buffer->err[last];
		
		if (buffer->err_msg)
			*msg = buffer->err_msg[last];
		else
			*msg = "message not provided.";
	}

	return code;
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

	buffer->is_static = 		data_is_static;
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

	Buffer_sign(buffer, 1, "");

	buffer->is_open = false;

	buffer->have_seek = !no_seek;

	buffer->id = 0;

	buffer->data_pos = 0; buffer->load_pos = 0;

	return buffer;
}

bool Buffer_is_active(Buffer* this) {
	if (this == nullptr) return false;

	
}

Buffer_ErrorCode Buffer_open(Buffer* this) {
	if (!Buffer_is_active(this))
		return Buffer_error(this, "Buffer is invalid", BUFFER_OPEN_ERROR);

	ErrorCode code = this->open(this);

	if (code != CODE_OK) return BUFFER_OPEN_ERROR;

	return BUFFER_OK;
}

Buffer_ErrorCode Buffer_seek(Buffer* this, ssize_t bytes, Buffer_FlagsSeek flag) {
	if (!Buffer_is_active(this)) return BUFFER_SEEK_ERROR;

	ErrorCode code = this->seek(this, bytes, flag);

	if (code != CODE_OK) return BUFFER_SEEK_ERROR;

	return BUFFER_OK;
}

Buffer_ErrorCode Buffer_write(Buffer* this, size_t start, const byte* data, size_t bytes, Buffer_Port port) {
	if (!Buffer_is_active(this)) return BUFFER_WRITE_ERROR;

	
}

Buffer_ErrorCode Buffer_read(Buffer* this, size_t start, byte* data, size_t bytes, Buffer_Port port) {
	if (!Buffer_is_active(this)) return CODE_FAIL;

	
}

Buffer_ErrorCode Buffer_write_byte(Buffer* this, byte data, Buffer_Port port) {
	if (!Buffer_is_active(this)) return CODE_FAIL;

	
}

Buffer_ErrorCode Buffer_read_byte(Buffer* this, byte* data, Buffer_Port port) {
	if (!Buffer_is_active(this)) return CODE_FAIL;

	
}

Buffer_ErrorCode Buffer_flush(Buffer* this, size_t bytes, Buffer_Port port) {
	if (!Buffer_is_active(this)) return CODE_FAIL;

	
}

Buffer_ErrorCode Buffer_fetch(Buffer* this, size_t bytes, Buffer_Port port) {
	if (!Buffer_is_active(this)) return CODE_FAIL;

	
}

Buffer_ErrorCode Buffer_fetch_count(Buffer* this, size_t* count, Buffer_Port port) {
	if (!Buffer_is_active(this)) return CODE_FAIL;

	
}

Buffer_ErrorCode Buffer_reset(Buffer* this) {
	if (!Buffer_is_active(this)) return CODE_FAIL;

	return this->reset(this);
}

Buffer_ErrorCode Buffer_close(Buffer* this) {
	if (!Buffer_is_active(this)) return CODE_FAIL;

	return this->close(this);
}

Buffer_ErrorCode Buffer_free(Buffer* this) {
	if (!Buffer_is_active(this)) return CODE_FAIL;

	ErrorCode code = this->free(this);

	if (code != CODE_OK)
		return BUFFER_FREE_ERROR;

	return CODE_OK;
}