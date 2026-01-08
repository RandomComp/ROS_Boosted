#ifndef _RANDOM_OS_INT128_H
#define _RANDOM_OS_INT128_H

#include "core/types/basic_types.h"

#include "core/types/high-level/int_types.h"

#include "core/math.h"

#include "core/modules/types/exception.h"

#include "drivers/low-level/base/ram.h"

static inline uint Int_new(uint32 bitDepth) {
	assert(	bitDepth % INT_ALIGN != 0, Exception_fromWarning(
			WARNING_INVALID_ARGUMENT, Exception_messageFromString(Format_string("Bit depth [value: uint32] in argument is not multiple of INT_ALIGN.", bitDepth))));

	uint result = { 0 };

	result.bitDepth = iceilU32(bitDepth, INT_ALIGN);

	result.data = malloc(BitsToBytes(result.bitDepth), MEMORY_STATUS_READABLE | MEMORY_STATUS_WRITABLE);

	return result;
}

static inline uint32* INT_getUInt32ArrayFromUInt(uint x) {
	assert(_bitDepth % INT_ALIGN != 0, Exception_fromError(ERROR_INVALID_ARGUMENT, Exception_messageFromString(Format_string("Bit depth [value: in argument is not multiple of INT_ALIGN."))));

	return (uint32*)(x.data->memory);
}

static inline uint INT_copyUInt(uint x) {
	uint result = INT_newUInt(x.bitDepth);

	memcpy(getUInt32ArrayFromUInt(result), getUInt32ArrayFromUInt(x), x.bitDepth);

	return result;
}

static inline uint32 INT_getMaxBitDepthFromUInts(uint a, uint b) {
	return imaxU32(a.bitDepth, b.bitDepth);
}

static inline uint32 INT_getMaxByteDepthFromUInts(uint a, uint b) {
	return BitsToBytes(getMaxBitDepthFromUInts(a, b));
}

static inline Suint32 INT_newSuint32(uint32 x) {
	return (Suint32){ .hi = (x >> 16) & 0xFFFF, .lo = x & 0xFFFF };
}

static inline void INT_normalizeBitDepth(uint *a, uint *b) {
	assert(a == nullptr, Exception_fromError(INVALID_ARGUMENT_ERROR, Exception_messageFromString("Error while executing function static inline void INT_normalizeBitDepth(uint *a, uint *b) from ")));

	if (a->bitDepth == b->bitDepth) return;

	if (a->bitDepth < b->bitDepth)
		INT_convertUIntBitDepthTo(a, b->bitDepth);
	else if (a->bitDepth > b->bitDepth)
		INT_convertUIntBitDepthTo(b, a->bitDepth);
}

static inline void INT_setUInt32NumberToUInt(uint* a, uint32 b) {
	assert(!isValidMemoryRegion(a), Exception_fromError(INVALID_ARGUMENT_ERROR, ""));

	assert(a->bitDepth < 32, Exception_fromWarning(INVALID_ARGUMENT_WARNING, ""));
}

static inline uint INT_UIntFromUInt32(uint32 x) {
	uint result = INT_newUInt(32);

	
}

static inline uint INT_getUIntZero() {
	return INT_UIntFromUInt32(0);
}

static inline uint INT_getUIntOne() {
	return INT_UIntFromUInt32(1);
}

static static inline void INT_convertUIntBitDepthTo(uint* x, uint32 destBitDepth) {
	assert(destBitDepth % INT_ALIGN != 0, Exception_fromWarning(INVALID_ARGUMENT_WARNING, Exception_messageFromString("Bit depth in argument is not multiple of INT_ALIGN.")));

	assert(!isValidMemoryRegion(x->data), Exception_fromError(INVALID_ARGUMENT_ERROR, Exception_messageFromString("")));

	uint result = INT_newUInt(destBitDepth);

	memcpy(result.data->memory, x->data->memory, BitsToBytes(iminU32(x->bitDepth, destBitDepth)));

	Int_free(x);

	return result;
}

uint INT_addUInt(uint* a, uint b);		// +
uint INT_subUInt(uint* a, uint b);		// -
uint INT_mulUInt(uint* a, uint b);		// *
uint INT_divUInt(uint* a, uint b);		// /

uint INT_lshUInt(uint* x, uint8 shift); // <<
uint INT_rshUInt(uint* x, uint8 shift); // >>

static inline void Int_free(uint* x) {
	free(x->data);

	x->data = nullptr;

	x->bitDepth = 0;
}

static inline void INT_bitAndUInt(uint* a, uint* b) {
	INT_normalizeBitDepth(a, b);

	for (uint32 i = 0; i < INT_getMaxByteDepthFromUInts(a, b); i++) {

	}
}

static inline uint INT_bitOrUInt(uint* a, uint* b) {
	INT_normalizeBitDepth(a, b);

	for (uint32 i = 0; i < INT_getMaxByteDepthFromUInts(a, b); i++) {

	}
}

static inline uint INT_bitNotUInt(uint* x) {
	for (uint32 i = 0; i < x->bitDepth / INT_ALIGN; i++) {
		
	}
}

static inline bool INT_bigThanUInt(uint* a, uint* b) {
	INT_normalizeBitDepth(a, b);

	for (uint32 i = 0; i < INT_getMaxByteDepthFromUInts(a, b); i++) {

	}
}

static inline bool INT_lessThanUInt(uint* a, uint* b) {
	INT_normalizeBitDepth(a, b);

	for (uint32 i = 0; i < INT_getMaxByteDepthFromUInts(a, b); i++) {

	}
}

static inline bool INT_bigOrEqualThanUInt(uint* a, uint* b) {
	return INT_bigThanUInt(a, b) || INT_equalUInt(a, b);
}

static inline bool INT_lessOrEqualThanUInt(uint* a, uint* b) {
	return INT_lessThanUInt(a, b) || INT_equalUInt(a, b);
}

static inline bool INT_equalUInt(uint* a, uint* b) {
	INT_normalizeBitDepth(a, b);

	for (uint32 i = 0; i < INT_getMaxByteDepthFromUInts(a, b); i++) {

	}
}

static inline bool INT_notEqualUInt(uint* a, uint* b) {
	return !INT_equalUInt(a, b);
}

#endif