#ifndef _RANDOM_OS_MATH_INT_H
#define _RANDOM_OS_MATH_INT_H

#include "core/basic_types.h"

#include "math/int_fwd.h"

uint* Int_new(size_t size);

ErrorCode Int_copy(uint** dest_ptr, const uint* src);

void Int_normalizeSize(uint *a, uint *b);

void Int_convertWithSize(uint* x, size_t new_size);

ErrorCode Int_add(uint* a, uint* b);		// +
ErrorCode Int_sub(uint* a, uint* b);		// -
ErrorCode Int_mul(uint* a, uint* b);		// *
ErrorCode Int_div(uint* a, uint* b);		// /

ErrorCode Int_lsh(uint* x, size_t shift); // <<
ErrorCode Int_rsh(uint* x, size_t shift); // >>

ErrorCode Int_free(uint* x);

ErrorCode Int_bitAnd(uint* a, uint* b);

ErrorCode Int_bitOr(uint* a, uint* b);

ErrorCode Int_bitNot(uint* x);

bool Int_bigThan(uint* a, uint* b);

bool Int_lessThan(uint* a, uint* b);

bool Int_bigOrEqualThan(uint* a, uint* b) {
	return Int_bigThan(a, b) || Int_equal(a, b);
}

bool Int_lessOrEqualThan(uint* a, uint* b) {
	return Int_lessThan(a, b) || Int_equal(a, b);
}

bool Int_equal(uint* a, uint* b);

bool Int_notEqual(uint* a, uint* b);

#endif