#ifndef _RANDOM_OS_INT_TYPES_H
#define _RANDOM_OS_INT_TYPES_H

#include "core/basic_types.h"

#include "drivers/memory/mem_types.h"

#define INT_ALIGN 4

#ifdef BITS_16
#define INT_ALIGN 2
#endif

#ifdef BITS_64
#define INT_ALIGN 8
#endif

typedef struct uint {
	uint32* data;

	uint32 byteDepth;
} uint;

typedef uint sint;

#endif