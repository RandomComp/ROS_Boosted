#include "math/int.h"

#include "math/int_types.h"

#include "math/int_fwd.h"

#include "math/math.h"

#include "drivers/memory/ram.h"

#include "builtins/mem.h"

#include "std/string/format.h"

#include "core/basic_types.h"

uint* Int_new(size_t size) {
	uint* result = malloc(sizeof(uint));

	if (result == nullptr) {
		throw(
			Exception_fromError(
				ERROR_MEMORY_LACK,
				"Failed to create new uint because malloc "
				"returned nullptr, so memory lack"
			)
		);

		return nullptr;
	}

	result->size = size;

	result->data = malloc(result->size * sizeof(word));

	if (result->data == nullptr) {
		throw(
			Exception_fromError(
				ERROR_MEMORY_LACK,
				"Failed to create new uint because malloc "
				"returned nullptr, so memory lack"
			)
		);

		return result;
	}

	memset(result->data, 0, result->size * sizeof(word));

	return result;
}

ErrorCode Int_free(uint* x) {
	if (x == nullptr) {
		throw(
			Exception_errorInvalidArgument(
				"Failed to free uint because uint* x is nullptr"
			)
		);

		return CODE_FAIL;
	}

	free(x->data);

	x->data = nullptr;

	x->size = 0;

	free(x);

	return CODE_OK;
}

ErrorCode Int_copy(uint** dest_ptr, const uint* src) {
	if (src == nullptr) {
		throw(
			Exception_errorInvalidArgument(
				"Failed to copy uint because uint* src is nullptr"
			)
		);

		return CODE_FAIL;
	}

	if (dest_ptr == nullptr) {
		throw(
			Exception_errorInvalidArgument(
				"Failed to copy uint because uint** dest_ptr is nullptr"
			)
		);

		return CODE_FAIL;
	}

	if (*dest_ptr == nullptr) {
		*dest_ptr = malloc(sizeof(uint));
	}

	uint* dest = *dest_ptr;

	memcpy(dest->data, src->data, src->size);

	return CODE_OK;
}

ErrorCode Int_normalizeSize(uint* a, uint* b) {
	if (a == nullptr) {
		throw(
			Exception_errorInvalidArgument(
				"uint* a is nullptr"
			)
		);

		return CODE_FAIL;
	}

	if (b == nullptr) {
		throw(
			Exception_errorInvalidArgument(
				"uint* b is nullptr"
			)
		);

		return CODE_FAIL;
	}

	if (a->size == b->size) return;

	if (a->size < b->size)
		Int_convertToWithSize(a, b->size);
	else if (a->size > b->size)
		Int_convertToWithSize(b, a->size);

	return CODE_OK;
}

void Int_setUInt32NumberToUInt(uint* a, size_t b) {
	assert(!isValidMemoryRegion(a), Exception_fromError(INVALID_ARGUMENT_ERROR, ""));

	assert(a->bitDepth < 32, Exception_fromWarning(INVALID_ARGUMENT_WARNING, ""));
}

uint Int_UIntFromUInt32(size_t x) {
	uint result = Int_newUInt(32);

	
}

uint Int_getUIntZero() {
	return Int_UIntFromUInt32(0);
}

uint Int_getUIntOne() {
	return Int_UIntFromUInt32(1);
}

ErrorCode Int_convertWithSize(uint* x, size_t new_size) {
	if (x == nullptr) {
		throw(
			Exception_errorInvalidArgument(
				"uint* x is null ptr"
			)
		);

		return CODE_FAIL;
	}

	if (x->data == nullptr) {
		throw(
			Exception_errorInvalidArgument(
				"word* uint::data x is null ptr"
			)
		);

		return CODE_FAIL;
	}
	
	word* new_data = realloc(x->data, new_size * sizeof(word));

	x->size = new_size;

	return CODE_OK;
}

static ErrorCode expand(uint* x, size_t amount) {
	if (x == nullptr) {
		throw(
			Exception_errorInvalidArgument(
				"uint* x is nullptr"
			)
		);

		return CODE_FAIL;
	}

	if (amount == 0) return CODE_OK;

	word* new_data = realloc(x->data, (x->size + amount) * sizeof(word));

	if (new_data == nullptr) {
		throw(
			Exception_fromError(
				ERROR_MEMORY_LACK,
				Format_c_str(
					"Failed to expand [value: size] because realloc "
					"returned nullptr, so memory lack", amount
				)
			)
		);

		return CODE_FAIL;
	}

	x->size += amount;

	x->data = new_data;

	return CODE_OK;
}

ErrorCode Int_add(uint* a, uint* b) {
	Int_normalizeSize(a, b); // if a->size = 1 and b->size = 2 then a->size = 2

	bool bOverflow = false;

	for (size_t i = 0; i < a->size; i++) {
		word* aPart = &a->data[i];

		word* bPart = &b->data[i];

		*aPart += *bPart;

		*aPart += bOverflow;

		bOverflow = (*aPart < *bPart);
	}

	if (bOverflow) {
		if (expand(a, 1) == CODE_FAIL)
			return CODE_FAIL;

		a->data[a->size - 1]++;
	}

	return CODE_OK;
}

void Int_sub(uint* a, uint* b) {
	Int_normalizeSize(a, b); // if a->size = 1 and b->size = 2 then a->size = 2

	bool bOverflow = false;

	for (size_t i = 0; i < a->size; i++) {
		word* aPart = &a->data[i];

		word* bPart = &b->data[i];

		*aPart -= *bPart;

		*aPart -= bOverflow;

		bOverflow = (*aPart > *bPart);
	}

	if (bOverflow) {
		if (expand(a, 1) == CODE_FAIL)
			return CODE_FAIL;

		a->data[a->size - 1]--;
	}

	return CODE_OK;
}


uint* Int_mul(uint a, uint b) {
	uint result = Int_new();

	// for (uint8 i = 0; i < 128; i++) {
	// 	if (checkBitU128(b, i)) {
	// 		result = addUInt128(result, lshUInt128(a, i));
	// 	}
	// }

	return result;
}

uint* Int_div(uint* a, uint* b) {
	// uint8 bLoDigitCount = getNumberOfDigitsU64(b.lo);

	// uint result = Int_rshUInt(Int_mulUInt(a, Int_UIntFromUInt32(0, 0x1000 / b.lo)), 12);

	// return result;
}

void Int_lshUInt(uint* x, size_t shift) {
	for (size_t i = shift; i < x->byteDepth; i += sizeof(x->data)) {

	}

	/*
	x.hi <<= shift; // Сдвиг ненулевых битов для получения свободного пространства для сдвига из lo 0...(shift - 1)

	x.hi |= (x.lo >> (63 - shift)); // Установка битов 64...(64 - shift) из lo в hi часть.
	
	x.lo <<= shift;
	*/
	
	return x;
}

void Int_rshUInt(uint* x, size_t shift) {
	if (shift >= x->bitDepth)
		return Int_convertToWithSize(x, iceilU32(shift, 32));

	if (shift <= 64) {
		x.lo >>= shift; // Сдвиг ненулевых битов для получения свободного пространства для сдвига из lo (shift - 1)...0
		
		x.lo |= (x.hi & makeIdentityMaskForU64(shift)) << (63 - shift); // Установка битов (shift - 1)...0 из hi в lo часть 64...(64 - shift).
		
		x.hi >>= shift; // Сдвиг и удаление битов из hi (shift - 1)...0.
	}

	else if (shift < 128) {
		Int_rshUInt(x, 64);

		Int_rshUInt(x, shift - 64);
	}
	
	return x;
}

void Int_bitAndUInt(uint* a, uint* b) {
	Int_normalizeSize(a, b);

	for (size_t i = 0; i < Int_getMaxByteDepthFromUInts(a, b); i++) {

	}
}

uint Int_bitOrUInt(uint* a, uint* b) {
	Int_normalizeSize(a, b);

	for (size_t i = 0; i < Int_getMaxByteDepthFromUInts(a, b); i++) {

	}
}

uint Int_bitNotUInt(uint* x) {
	for (size_t i = 0; i < x->bitDepth / Int_ALIGN; i++) {
		
	}
}

bool Int_bigThanUInt(uint* a, uint* b) {
	Int_normalizeSize(a, b);

	for (size_t i = 0; i < Int_getMaxByteDepthFromUInts(a, b); i++) {

	}
}

bool Int_lessThanUInt(uint* a, uint* b) {
	Int_normalizeSize(a, b);

	for (size_t i = 0; i < Int_getMaxByteDepthFromUInts(a, b); i++) {

	}
}

bool Int_equalUInt(uint* a, uint* b) {
	Int_normalizeSize(a, b);

	for (size_t i = 0; i < Int_getMaxByteDepthFromUInts(a, b); i++) {

	}
}

bool Int_notEqualUInt(uint* a, uint* b) {
	return !Int_equalUInt(a, b);
}