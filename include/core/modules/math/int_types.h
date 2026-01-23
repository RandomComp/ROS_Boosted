#ifndef _RANDOM_OS_INT_TYPES_H
#define _RANDOM_OS_INT_TYPES_H

#include "core/basic_types.h"

struct uint {
	#ifdef BITS_32
		uint32* data;
	#elifdef BITS_64
		uint64* data;
	#else BITS_16
		uint8* data;
	#endif

	size_t size;
};

#endif