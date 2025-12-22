#ifndef _RANDOM_OS_INT128_H
#define _RANDOM_OS_INT128_H

#include "core/types.h"

typedef struct uint128 {
	uint64 hi, lo;
} uint128;

const uint128 UINT128_ZERO = (uint128){.hi = 0, .lo = 0 };

const uint128 UINT128_ONE = (uint128){.hi = 0, .lo = 1 };

inline uint128 newUInt128(uint64 hi, uint64 lo) {
	return (uint128){.hi = hi, .lo = lo };
}

inline uint128 newUInt128FromUInt64(uint64 x) {
	return (uint128){.hi = 0, .lo = x };
}

inline uint64* getU64BitPartFromUInt128(uint128* x, uint8 bitIndex) {
	if (bitIndex >= 128); // TODO: Handle error

	return bitIndex >= 64 ? &x->hi : &x->lo;
}

uint128 addUInt128(uint128 a, uint128 b);		// +
uint128 subUInt128(uint128 a, uint128 b);		// -
uint128 mulUInt128(uint128 a, uint128 b);		// *
uint128 divUInt128(uint128 a, uint128 b);		// /

uint128 lshUInt128(uint128 x, uint8 shift); 	// <<
uint128 rshUInt128(uint128 x, uint8 shift); 	// >>

inline uint128 bitAndUInt128(uint128 a, uint128 b) {
	return newUInt128(a.hi & b.hi, a.lo & b.lo);
}

inline uint128 bitOrUInt128(uint128 a, uint128 b) {
	return newUInt128(a.hi | b.hi, a.lo | b.lo);
}

inline uint128 bitNotUInt128(uint128 x) {
	return newUInt128(~x.hi, ~x.lo);
}

inline bool bigThanUInt128(uint128 a, uint128 b) {
	return a.hi > b.hi || (a.hi == b.hi && a.lo > b.lo);
}

inline bool lessThanUInt128(uint128 a, uint128 b) {
	return a.hi < b.hi || (a.hi == b.hi && a.lo < b.lo);
}

inline bool bigOrEqualThanUInt128(uint128 a, uint128 b) {
	return a.hi > b.hi || (a.hi == b.hi && a.lo >= b.lo);
}

inline bool lessOrEqualThanUInt128(uint128 a, uint128 b) {
	return a.hi < b.hi || (a.hi == b.hi && a.lo <= b.lo);
}

inline bool equalUInt128(uint128 a, uint128 b) {
	return a.hi == b.hi && a.lo == b.lo;
}

inline bool notEqualUInt128(uint128 a, uint128 b) {
	return a.hi != b.hi || a.lo != b.lo;
}

#endif