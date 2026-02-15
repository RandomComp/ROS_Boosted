#ifndef _RANDOM_OS_BUFFER_H
#define _RANDOM_OS_BUFFER_H

#include "core/basic_types.h"

#include "buffer/buffer_fwd.h"

bool Buffer_isValid(Buffer* buffer);
const c_str Buffer_whyInvalid(Buffer* buffer);
bool Buffer_checkForActiveBuffer(Buffer* buffer);

ErrorCode Buffer_sendID(Buffer* this);
ErrorCode Buffer_freeID(Buffer* this);
ErrorCode Buffer_newID(Buffer* this);

ErrorCode Buffer_waitForBytes(Buffer* this);

ErrorCode Buffer_resize(Buffer* this, size_t size, size_t context_size);
ErrorCode Buffer_increase(Buffer* this, size_t size, size_t context_size);

byte* Buffer_checksum(Buffer* buffer);

Buffer* Buffer_new(size_t size, size_t context_size, Buffer_CreationFlags flags);

#endif