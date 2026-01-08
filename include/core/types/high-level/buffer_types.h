#ifndef _RANDOM_OS_BUFFER_TYPES_H
#define _RANDOM_OS_BUFFER_TYPES_H

#include "core/types/basic_types.h"

#include "core/types/high-level/T_types.h"

typedef struct Buffer {
    byte* data;

    byte* optionalData;

    size_t size;

    size_t optionalDataSize;

    void (*open)(Buffer* self);

    void (*write)(Buffer* self, uint32 start, uint32 end, T data);
    void (*read)(Buffer* self, uint32 start, uint32 end, T* data);

    void (*flush)(Buffer* self, uint32 bytes);
    void (*fetch)(Buffer* self, uint32 bytes);

    void (*close)(Buffer* self);
} Buffer;

Buffer Buffer_newBasicBuffer();

#endif