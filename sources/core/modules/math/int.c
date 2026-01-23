#include "math/int.h"

#include "math/int_types.h"

#include "math/int_fwd.h"

#include "math/math.h"

#include "core/basic_types.h"

uint Int_new(uint32 byteDepth) {
	if (byteDepth % INT_ALIGN != 0) {
		throw(
			Exception_warningInvalidArgument(
				Format_c_str(
					"Byte depth [value: u32] in argument is not "
					"multiple of INT_ALIGN=[value: u32].", byteDepth, INT_ALIGN
				)
			)
		);
	}

	uint result = { 0 };

	result.size = ceilU32(byteDepth, INT_ALIGN);

	result.data = malloc(result.size, MEMORY_STATUS_ACTIVE);

	memset(result.data, 0, result.byteDepth);

	return result;
}

void Int_free(uint* x) {
	free(x->data);

	x->data = nullptr;

	x->bitDepth = 0;
}

uint INT_copyUInt(uint x) {
	uint result = INT_newUInt(x.bitDepth);

	memcpy(getUInt32ArrayFromUInt(result), getUInt32ArrayFromUInt(x), x.bitDepth);

	return result;
}

uint32 INT_getMaxBitDepthFromUInts(uint a, uint b) {
	return imaxU32(a.bitDepth, b.bitDepth);
}

uint32 INT_getMaxByteDepthFromUInts(uint a, uint b) {
	return BitsToBytes(getMaxBitDepthFromUInts(a, b));
}

Suint32 INT_newSuint32(uint32 x) {
	return (Suint32){ .hi = (x >> 16) & 0xFFFF, .lo = x & 0xFFFF };
}

void INT_normalizeBitDepth(uint *a, uint *b) {
	assert(a == nullptr, Exception_fromError(INVALID_ARGUMENT_ERROR, Exception_fromString("Error while executing function void INT_normalizeBitDepth(uint *a, uint *b) from ")));

	if (a->bitDepth == b->bitDepth) return;

	if (a->bitDepth < b->bitDepth)
		INT_convertUIntBitDepthTo(a, b->bitDepth);
	else if (a->bitDepth > b->bitDepth)
		INT_convertUIntBitDepthTo(b, a->bitDepth);
}

void INT_setUInt32NumberToUInt(uint* a, uint32 b) {
	assert(!isValidMemoryRegion(a), Exception_fromError(INVALID_ARGUMENT_ERROR, ""));

	assert(a->bitDepth < 32, Exception_fromWarning(INVALID_ARGUMENT_WARNING, ""));
}

uint INT_UIntFromUInt32(uint32 x) {
	uint result = INT_newUInt(32);

	
}

uint INT_getUIntZero() {
	return INT_UIntFromUInt32(0);
}

uint INT_getUIntOne() {
	return INT_UIntFromUInt32(1);
}

void INT_convertUIntBitDepthTo(uint* x, uint32 destBitDepth) {
	assert(destBitDepth % INT_ALIGN != 0, Exception_fromWarning(INVALID_ARGUMENT_WARNING, Exception_fromString("Bit depth in argument is not multiple of INT_ALIGN.")));

	assert(!isValidMemoryRegion(x->data), Exception_fromError(INVALID_ARGUMENT_ERROR, Exception_fromString("")));

	uint result = INT_newUInt(destBitDepth);

	memcpy(result, x, BitsToBytes(iminU32(x->bitDepth, destBitDepth)));

	Int_free(x);

	return result;
}

void Int_addUInt(uint* a, uint* b) {
	// result.lo += b.lo;

	// result.hi += b.hi + (result.lo < b.lo); // hi = 1011, lo = 0001 1001, 1100 1001

	Int_normalizeBitDepth(a, b);

	bool bOverflow = false;

	for (uint32 i = 0; i < a->byteDepth / 4; i++) {
		uint32* aPart = &a->data[i];

		uint32* bPart = &b->data[i];

		*aPart += *bPart;

		*aPart += bOverflow;

		bOverflow = (*aPart < *bPart);
	}
}

void INT_subUInt(uint* a, uint* b) {
	// uint result = a;

	// result.lo -= b.lo;

	// result.hi -= b.hi - (result.lo > b.lo);

	Int_normalizeBitDepth(a, b);

	bool bOverflow = false;

	for (uint32 i = 0; i < a->byteDepth / 4; i++) {
		uint32* aPart = &a->data[i];

		uint32* bPart = &b->data[i];

		*aPart -= *bPart;

		*aPart -= bOverflow;

		bOverflow = (*aPart > *bPart);
	}
}


uint INT_mulUInt(uint a, uint b) {
	uint result = INT_getUIntZero();

	// for (uint8 i = 0; i < 128; i++) {
	// 	if (checkBitU128(b, i)) {
	// 		result = addUInt128(result, lshUInt128(a, i));
	// 	}
	// }

	return result;
}

uint INT_divUInt(uint a, uint b) {
	// uint8 bLoDigitCount = getNumberOfDigitsU64(b.lo);

	// uint result = INT_rshUInt(INT_mulUInt(a, INT_UIntFromUInt32(0, 0x1000 / b.lo)), 12);

	// return result;
}

void INT_lshUInt(uint* x, uint32 shift) {
	for (size_t i = shift; i < x->byteDepth; i += sizeof(x->data)) {

	}

	/*
	x.hi <<= shift; // Сдвиг ненулевых битов для получения свободного пространства для сдвига из lo 0...(shift - 1)

	x.hi |= (x.lo >> (63 - shift)); // Установка битов 64...(64 - shift) из lo в hi часть.
	
	x.lo <<= shift;
	*/
	
	return x;
}

void INT_rshUInt(uint* x, uint32 shift) {
	if (shift >= x->bitDepth)
		return INT_convertUIntBitDepthTo(x, iceilU32(shift, 32));

	if (shift <= 64) {
		x.lo >>= shift; // Сдвиг ненулевых битов для получения свободного пространства для сдвига из lo (shift - 1)...0
		
		x.lo |= (x.hi & makeIdentityMaskForU64(shift)) << (63 - shift); // Установка битов (shift - 1)...0 из hi в lo часть 64...(64 - shift).
		
		x.hi >>= shift; // Сдвиг и удаление битов из hi (shift - 1)...0.
	}

	else if (shift < 128) {
		INT_rshUInt(x, 64);

		INT_rshUInt(x, shift - 64);
	}
	
	return x;
}

void INT_bitAndUInt(uint* a, uint* b) {
	INT_normalizeBitDepth(a, b);

	for (uint32 i = 0; i < INT_getMaxByteDepthFromUInts(a, b); i++) {

	}
}

uint INT_bitOrUInt(uint* a, uint* b) {
	INT_normalizeBitDepth(a, b);

	for (uint32 i = 0; i < INT_getMaxByteDepthFromUInts(a, b); i++) {

	}
}

uint INT_bitNotUInt(uint* x) {
	for (uint32 i = 0; i < x->bitDepth / INT_ALIGN; i++) {
		
	}
}

bool INT_bigThanUInt(uint* a, uint* b) {
	INT_normalizeBitDepth(a, b);

	for (uint32 i = 0; i < INT_getMaxByteDepthFromUInts(a, b); i++) {

	}
}

bool INT_lessThanUInt(uint* a, uint* b) {
	INT_normalizeBitDepth(a, b);

	for (uint32 i = 0; i < INT_getMaxByteDepthFromUInts(a, b); i++) {

	}
}

bool INT_bigOrEqualThanUInt(uint* a, uint* b) {
	return INT_bigThanUInt(a, b) || INT_equalUInt(a, b);
}

bool INT_lessOrEqualThanUInt(uint* a, uint* b) {
	return INT_lessThanUInt(a, b) || INT_equalUInt(a, b);
}

bool INT_equalUInt(uint* a, uint* b) {
	INT_normalizeBitDepth(a, b);

	for (uint32 i = 0; i < INT_getMaxByteDepthFromUInts(a, b); i++) {

	}
}

bool INT_notEqualUInt(uint* a, uint* b) {
	return !INT_equalUInt(a, b);
}