#ifndef _RANDOM_OS_MATH_INT_H
#define _RANDOM_OS_MATH_INT_H

#include "core/basic_types.h"

#include "math/int_fwd.h"

#include "math/math.h"

#include "exceptions/exception.h"

#include "drivers/memory/ram.h"

#include "builtins/mem.h"

uint Int_new(uint32 byteDepth);

uint INT_copyUInt(uint x);

uint32 INT_getMaxBitDepthFromUInts(uint a, uint b);

uint32 INT_getMaxByteDepthFromUInts(uint a, uint b);

void INT_normalizeBitDepth(uint *a, uint *b);

void INT_setUInt32NumberToUInt(uint* a, uint32 b);

uint INT_UIntFromUInt32(uint32 x);

void INT_convertUIntBitDepthTo(uint* x, uint32 destBitDepth);

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