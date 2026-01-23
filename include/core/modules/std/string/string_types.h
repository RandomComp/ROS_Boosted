#ifndef _RANDOM_OS_STD_STRING_TYPES_H
#define _RANDOM_OS_STD_STRING_TYPES_H

#include "core/basic_types.h"

#include "std/string/char_types.h"

typedef struct String {
	size_t length;

	void* data;
} String;

#endif