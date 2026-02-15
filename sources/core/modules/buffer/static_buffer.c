#include "buffer/static_buffer.h"

#include "buffer/buffer.h"

#include "buffer/buffer_types.h"

#include "std/std.h"

Buffer* StaticBuffer_new(byte* ptr, size_t size) {
	if (ptr == nullptr) {
		klog(LOG_ERROR, "Static buffer creation failure: requested ptr is nullptr\n");

		return nullptr;
	}

	Buffer* buffer = Buffer_new(0, 0, BUFFER_CREATION_STATIC);

	if (buffer == nullptr) {
		klog(LOG_CRITICAL, "Static buffer creation failure: Buffer_new returned nullptr (out of memory)\n");

		return nullptr;
	}

	buffer->data = ptr;
	buffer->data_size = size;

	buffer->sig[8] =  'S';
	buffer->sig[9] =  'T';
	buffer->sig[10] = 'A';
	buffer->sig[11] = 'T';
	buffer->sig[12] = 'I';
	buffer->sig[13] = 'C';
	buffer->sig[14] = '\0';

	return buffer;
}