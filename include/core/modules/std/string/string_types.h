#ifndef _RANDOM_OS_STRING_TYPES_H
#define _RANDOM_OS_STRING_TYPES_H

#include "core/basic_types.h"

#include "core/modules/std/string/char_types.h"

#include "drivers/memory/mem_types.h"

typedef Char* char_ptr;

typedef String* str_ptr;

typedef struct String {
	size_t length;

	MemoryRegion* region;
} String;

#endif