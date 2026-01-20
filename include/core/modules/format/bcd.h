#ifndef _RANDOM_OS_FORMAT_BCD_H
#define _RANDOM_OS_FORMAT_BCD_H

#include "core/basic_types.h"

#include "core/modules/math/int_types.h"

#include "core/modules/exceptions/exception.h"

// TODO: Написать единую функцию для преобразования числа в строку, включая дробные.

static inline uint8 getByteIndex(uint32 value) {
	return value / 8;
}

static inline uint8 getBitIndex(uint32 value) {
	return value % 8;
}

uint32 toBCDU32(uint32 num);

uint32 fromBCDU32(uint32 num);

uint64 toBCDU64(uint64 num);

uint64 fromBCDU64(uint64 num);

#endif