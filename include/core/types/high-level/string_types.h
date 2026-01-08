#ifndef _RANDOM_OS_STRING_TYPES_H
#define _RANDOM_OS_STRING_TYPES_H

#include "core/types/basic_types.h"

#include "core/types/high-level/virtual_ram_types.h"

typedef Char* char_ptr;

typedef String* str_ptr;

typedef struct String {
	size_t length;

	VirtualMemoryRegion* region;
} String;

#endif