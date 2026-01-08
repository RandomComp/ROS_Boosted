#ifndef _RANDOM_OS_VRAM_TYPES_H
#define _RANDOM_OS_VRAM_TYPES_H

#include "core/types/basic_types.h"

#include "core/types/high-level/buffer_types.h"

#include "core/types/low-level/mem_types.h"

typedef struct VirtualMemoryRegion {

    Buffer buffer; // Буфер для работы
} VirtualMemoryRegion;

#endif