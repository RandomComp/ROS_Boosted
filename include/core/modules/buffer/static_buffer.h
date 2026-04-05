#ifndef _R_OS_STATIC_BUFFER_H
#define _R_OS_STATIC_BUFFER_H

#include "core/basic_types.h"

#include "buffer/buffer_fwd.h"

Buffer* StaticBuffer_new(byte* ptr, size_t size);

#endif