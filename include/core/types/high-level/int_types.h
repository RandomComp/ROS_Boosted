#ifndef _RANDOM_OS_INT_TYPES_H
#define _RANDOM_OS_INT_TYPES_H

#include "core/types/basic_types.h"

#include "drivers/low-level/base/mem_types.h"

#define INT_ALIGN 32

#ifdef BITS_16
#define INT_ALIGN 16
#endif

#ifdef BITS_64
#define INT_ALIGN 64
#endif

typedef struct uint {
	MemoryRegion* data;

	uint32 bitDepth;
} uint;

typedef uint sint;

#endif