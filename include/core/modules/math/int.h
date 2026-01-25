#ifndef _RANDOM_OS_MATH_INT_H
#define _RANDOM_OS_MATH_INT_H

#include "core/basic_types.h"

ErrorCode Int_new(size_t size);

ErrorCode Int_copy(uint** dest_ptr, const uint* src);

void Int_normalizeSize(uint *a, uint *b);

void Int_setUInt32NumberToUInt(uint* a, size_t b);

uint Int_UIntFromUInt32(size_t x);

void Int_convertToWithSize(uint* x, size_t new_size);

ErrorCode Int_add(uint* a, uint* b);		// +
ErrorCode Int_sub(uint* a, uint* b);		// -
ErrorCode Int_mul(uint* a, uint* b);		// *
ErrorCode Int_div(uint* a, uint* b);		// /

ErrorCode Int_lsh(uint* x, size_t shift); // <<
ErrorCode Int_rsh(uint* x, size_t shift); // >>

void Int_free(uint* x);

void Int_bitAndUInt(uint* a, uint* b);

uint Int_bitOrUInt(uint* a, uint* b);

uint Int_bitNotUInt(uint* x);

bool Int_bigThanUInt(uint* a, uint* b);

bool Int_lessThanUInt(uint* a, uint* b);

bool Int_bigOrEqualThanUInt(uint* a, uint* b) {
	return Int_bigThanUInt(a, b) || Int_equalUInt(a, b);
}

bool Int_lessOrEqualThanUInt(uint* a, uint* b) {
	return Int_lessThanUInt(a, b) || Int_equalUInt(a, b);
}

bool Int_equalUInt(uint* a, uint* b);

bool Int_notEqualUInt(uint* a, uint* b);

#endif