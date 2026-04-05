#ifndef _R_OS_STD_STRING_TYPES_H
#define _R_OS_STD_STRING_TYPES_H

#include "core/basic_types.h"

#include "std/string/string_fwd.h"

struct String {
	size_t length;

	void* data;
};

#endif