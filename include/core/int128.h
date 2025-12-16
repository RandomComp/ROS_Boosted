#ifndef _RANDOM_OS_INT128_H
#define _RANDOM_OS_INT128_H

#include "core/types.h"

typedef struct uint128 {
	uint64 hi, lo;
} uint128;

inline uint128 newUInt128(uint64 hi, uint64 lo) {
	return (uint128){.hi = hi, .lo = lo};
}

uint128 addUInt128(uint128 a, uint128 b);

uint128 subUInt128(uint128 a, uint128 b);

uint128 mulUInt128(uint128 a, uint128 b);

uint128 divUInt128(uint128 a, uint128 b);

uint128 bitAndUInt128(uint128 a, uint128 b);

uint128 bitOrUInt128(uint128 a, uint128 b);

#endif