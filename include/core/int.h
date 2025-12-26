#ifndef _RANDOM_OS_INT128_H
#define _RANDOM_OS_INT128_H

#include "core/types.h"

#include "core/math.h"

#include "core/exception.h"

#include "drivers/low-level/base/ram.h"

#define INT_ALIGN 32

typedef struct uint {
	MemoryRegion* data;

	uint32 bitDepth;
} uint;

typedef struct sint {
	uint x;

	bool bSign;
} sint;

typedef struct Suint32 {
	uint16 hi, lo;
} Suint32;

inline uint INT_newUInt(uint32 bitDepth) {
	uint result = { 0 };

	result.bitDepth = bitDepth;

	result.data = malloc(BitsToBytes(bitDepth), MEMORY_STATUS_READABLE | MEMORY_STATUS_WRITABLE);

	return result;
}

inline uint32* INT_getUInt32ArrayFromUInt(uint x) {
	return (uint32*)(x.data->memory);
}

inline uint INT_copyUInt(uint x) {
	uint result = INT_newUInt(x.bitDepth);

	memcpy(getUInt32ArrayFromUInt(result), getUInt32ArrayFromUInt(x), x.bitDepth);

	return result;
}

inline uint32 INT_getMaxBitDepthFromUInts(uint a, uint b) {
	return imaxU32(a.bitDepth, b.bitDepth);
}

inline uint32 INT_getMaxByteDepthFromUInts(uint a, uint b) {
	return BitsToBytes(getMaxBitDepthFromUInts(a, b));
}

inline Suint32 INT_newSuint32(uint32 x) {
	return (Suint32){ .hi = (x >> 16) & 0xFFFF, .lo = x & 0xFFFF };
}

inline void INT_normalizeBitDepth(uint *a, uint *b) {
	assert(a == nullptr, Exception_fromError(INVALID_ARGUMENT_ERROR, "Error while executing function inline void INT_normalizeBitDepth(uint *a, uint *b) from "));

	if (a->bitDepth == b->bitDepth) return;

	if (a->bitDepth < b->bitDepth)
		INT_convertUIntBitDepthTo(a, b->bitDepth);
	else if (a->bitDepth > b->bitDepth)
		INT_convertUIntBitDepthTo(b, a->bitDepth);
}

inline void INT_setUInt32NumberToUInt(uint* a, uint32 b) {
	assert(!isValidAndActiveMemoryRegion(a), Exception_fromError(INVALID_ARGUMENT_ERROR, ""));

	assert(a->bitDepth < 32, Exception_fromWarning(INVALID_ARGUMENT_WARNING, ""));
}

inline uint INT_UIntFromUInt32(uint32 x) {
	uint result = INT_newUInt(32);

	
}

inline uint INT_getUIntZero() {
	return INT_UIntFromUInt32(0);
}

inline uint INT_getUIntOne() {
	return INT_UIntFromUInt32(1);
}

static inline void INT_convertUIntBitDepthTo(uint* x, uint32 destBitDepth) {
	if (destBitDepth % INT_ALIGN != 0) warn(BIT_DEPTH_IS_NOT_MULTIPLE_OF_INT_ALIGN_WARNING);

	assert(destBitDepth % INT_ALIGN != 0, )

	if (!isValidAndActiveMemoryRegion(x->data)) cause(INCORRECT_ARGUMENT_ERROR);

	assert(!isValidAndActiveMemoryRegion(x->data), ExceptionFromError());

	uint result = INT_newUInt(iceilU32(destBitDepth, INT_ALIGN));

	memcpy(result.data->memory, x->data->memory, BitsToBytes(iminU32(x->bitDepth, destBitDepth)));

	return result;
}

uint INT_addUInt(uint* a, uint b);		// +
uint INT_subUInt(uint* a, uint b);		// -
uint INT_mulUInt(uint* a, uint b);		// *
uint INT_divUInt(uint* a, uint b);		// /

uint INT_lshUInt(uint* x, uint8 shift); // <<
uint INT_rshUInt(uint* x, uint8 shift); // >>

inline uint INT_bitAndUInt(uint _a, uint _b) {
	int32 maxBitDepth = getMaxBitDepthFromUInts(_a, _b);

	uint 	a = INT_convertUIntBitDepthTo(_a, maxBitDepth), 
			b = INT_convertUIntBitDepthTo(_b, maxBitDepth);

	uint result = INT_copyUInt(a);

	for (uint32 i = 0; i < getMaxByteDepthFromUInts(a, b); i++) {

	}

	return result;
}

inline uint INT_bitOrUInt(uint a, uint b) {
	return INT_newUInt128(a.hi | b.hi, a.lo | b.lo);
}

inline uint INT_bitNotUInt(uint x) {
	return INT_newUInt128(~x.hi, ~x.lo);
}

inline bool INT_bigThanUInt(uint a, uint b) {
	return a.hi > b.hi || (a.hi == b.hi && a.lo > b.lo);
}

inline bool INT_lessThanUInt(uint a, uint b) {
	return a.hi < b.hi || (a.hi == b.hi && a.lo < b.lo);
}

inline bool INT_bigOrEqualThanUInt(uint a, uint b) {
	return a.hi > b.hi || (a.hi == b.hi && a.lo >= b.lo);
}

inline bool INT_lessOrEqualThanUInt(uint a, uint b) {
	return a.hi < b.hi || (a.hi == b.hi && a.lo <= b.lo);
}

inline bool INT_equalUInt(uint a, uint b) {
	return a.hi == b.hi && a.lo == b.lo;
}

inline bool INT_notEqualUInt(uint a, uint b) {
	return a.hi != b.hi || a.lo != b.lo;
}

#endif