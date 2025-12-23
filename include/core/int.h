#ifndef _RANDOM_OS_INT128_H
#define _RANDOM_OS_INT128_H

#include "core/types.h"

#include "core/math.h"

#include "core/warning.h"

#include "drivers/low-level/base/mem.h"

typedef struct uint {
	MemoryRegion* data;

	uint32 bitDepth;
} uint;

typedef struct Suint32 {
	uint16 hi, lo;
} Suint32;

inline uint getUIntZero() {
	return newUInt128(0, 0, 0, 0);
}

inline uint getUIntOne() {
	return newUInt128(0, 0, 0, 1);
}

inline uint newUInt(uint32 bitDepth) {
	uint result = { 0 };

	result.bitDepth = bitDepth;

	result.data = malloc(BitsToBytes(bitDepth), MEMORY_ACCESS_WRITE | MEMORY_ACCESS_READ);

	return result;
}

inline uint32* getUInt32ArrayFromUInt(uint x) {
	return (uint32*)(x.data->memory);
}

inline uint newUInt128(uint32 hihi, uint32 hilo, uint32 lohi, uint32 lolo) {
	uint result = newUInt(128);

	uint32* data = getUInt32ArrayFromUInt(result);

	data[0] = lolo;
	data[1] = lohi;
	data[2] = hilo;
	data[3] = hihi;

	return result;
}

inline uint copyUInt(uint x) {
	uint result = newUInt(x.bitDepth);

	memcpy(getUInt32ArrayFromUInt(result), getUInt32ArrayFromUInt(x), x.bitDepth);

	return result;
}

inline uint32 getMaxBitDepthFromUInts(uint a, uint b) {
	return imaxU32(a.bitDepth, b.bitDepth);
}

inline uint32 getMaxByteDepthFromUInts(uint a, uint b) {
	return BitsToBytes(getMaxBitDepthFromUInts(a, b));
}

inline uint newUInt128FromUInt64(uint32 hi, uint32 lo) {
	return newUInt128(0, 0, hi, lo);
}

inline Suint32 newSuint32(uint32 x) {
	return (Suint32){ .hi = (x >> 16) & 0xFFFF, .lo = x & 0xFFFF };
}

inline void normalizeBitDepth(uint *a, uint *b) {
	if (a->bitDepth == b->bitDepth) return;

	else if (a->bitDepth < b->bitDepth)
		*a = convertUIntBitDepthTo(*a, b->bitDepth);
	else if (a->bitDepth > b->bitDepth)
		*b = convertUIntBitDepthTo(*b, a->bitDepth);
}

inline uint convertUIntBitDepthTo(uint x, uint32 destBitDepth) {
	if (destBitDepth % 8 != 0) warn();

	uint result = newUInt(destBitDepth);

	memcpy(result.data->memory, x.data->memory, BitsToBytes(x.bitDepth));

	return result;
}

uint addUInt(uint a, uint b);		// +
uint subUInt(uint a, uint b);		// -
uint mulUInt(uint a, uint b);		// *
uint divUInt(uint a, uint b);		// /

uint lshUInt(uint x, uint8 shift); 	// <<
uint rshUInt(uint x, uint8 shift); 	// >>

inline uint bitAndUInt(uint _a, uint _b) {
	int32 maxBitDepth = getMaxBitDepthFromUInts(_a, _b);

	uint 	a = convertUIntBitDepthTo(_a, maxBitDepth), 
			b = convertUIntBitDepthTo(_b, maxBitDepth);

	uint result = copyUInt(a);

	for (uint32 i = 0; i < getMaxByteDepthFromUInts(a, b); i++) {

	}

	return result;
}

inline uint bitOrUInt(uint a, uint b) {
	return newUInt128(a.hi | b.hi, a.lo | b.lo);
}

inline uint bitNotUInt(uint x) {
	return newUInt128(~x.hi, ~x.lo);
}

inline bool bigThanUInt(uint a, uint b) {
	return a.hi > b.hi || (a.hi == b.hi && a.lo > b.lo);
}

inline bool lessThanUInt(uint a, uint b) {
	return a.hi < b.hi || (a.hi == b.hi && a.lo < b.lo);
}

inline bool bigOrEqualThanUInt(uint a, uint b) {
	return a.hi > b.hi || (a.hi == b.hi && a.lo >= b.lo);
}

inline bool lessOrEqualThanUInt(uint a, uint b) {
	return a.hi < b.hi || (a.hi == b.hi && a.lo <= b.lo);
}

inline bool equalUInt(uint a, uint b) {
	return a.hi == b.hi && a.lo == b.lo;
}

inline bool notEqualUInt(uint a, uint b) {
	return a.hi != b.hi || a.lo != b.lo;
}

#endif