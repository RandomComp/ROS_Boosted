#include "math/int.h"

#include "math/int_types.h"

#include "math/int_fwd.h"

#include "math/math.h"

#include "math/bit_math.h"

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
				"returned nullptr (out of memory)"
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
				"returned nullptr (out of memory)"
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
		*dest_ptr = Int_new(src->size);

		if (*dest_ptr == nullptr) {
			throw(
				Exception_fromError(
					ERROR_MEMORY_LACK,
					"Failed to copy uint because malloc returned nullptr for dest (out of memory)"
				)
			);

			return CODE_FAIL;
		}
	}

	uint* dest = *dest_ptr;

	size_t size_to_copy = MIN(dest->size, src->size);

	memcpy(dest->data, src->data, size_to_copy);

	return CODE_OK;
}

ErrorCode Int_normalizeSize(uint* a, uint* b) {
	if (a == nullptr) {
		throw(
			Exception_errorInvalidArgument(
				"Failed to normalize size for uint's because uint* a is nullptr"
			)
		);

		return CODE_FAIL;
	}

	if (b == nullptr) {
		throw(
			Exception_errorInvalidArgument(
				"Failed to normalize size for uint's because uint* b is nullptr"
			)
		);

		return CODE_FAIL;
	}

	if (a->size == b->size) return CODE_OK;

	if (a->size < b->size)
		Int_convertWithSize(a, b->size);
	else if (a->size > b->size)
		Int_convertWithSize(b, a->size);

	return CODE_OK;
}

ErrorCode Int_convertWithSize(uint* x, size_t new_size) {
	if (x == nullptr) {
		throw(
			Exception_errorInvalidArgument(
				"Failed to convert uint* x size because uint* x is nullptr"
			)
		);

		return CODE_FAIL;
	}

	if (x->data == nullptr) {
		throw(
			Exception_errorInvalidArgument(
				"Failed to convert uint* x size because x->data is nullptr"
			)
		);

		return CODE_FAIL;
	}
	
	word* new_data = realloc(x->data, new_size * sizeof(word));

	if (new_data == nullptr) {
		throw(
			Exception_fromError(
				ERROR_MEMORY_LACK,
				"Failed to convert uint* x size because realloc returned nullptr (out of memory)"
			)
		);

		return CODE_FAIL;
	}

	x->size = new_size;

	x->data = new_data;

	return CODE_OK;
}

static ErrorCode expand(uint* x, size_t amount) {
	if (amount == 0) return CODE_OK;

	if (x == nullptr) {
		throw(
			Exception_errorInvalidArgument(
				Format_c_str(
					"Failed to expand uint* x with [value: size] because x is nullptr",
					amount * sizeof(word)
				)
			)
		);

		return CODE_FAIL;
	}

	ErrorCode error = Int_convertWithSize(x, x->size + amount);

	if (error == CODE_FAIL) {
		throw(
			Exception_errorInvalidArgument(
				Format_c_str(
					"Failed to expand uint* x with [value: size] because "
					"Int_convertWithSize returned CODE_FAIL",
					amount * sizeof(word)
				)
			)
		);

		return CODE_FAIL;
	}

	return CODE_OK;
}

ErrorCode Int_add(uint* a, uint* b) {
	if (a->size == 0) {
		throw(
			Exception_errorInvalidArgument(
				""
			)
		);

		return CODE_FAIL;
	}

	Int_normalizeSize(a, b);

	size_t min_size = MIN(a->size, b->size);

	bool overflow = false;

	for (size_t i = 0; i < a->size; i++) {
		word* aPart = &a->data[i];

		word* bPart = &b->data[i];

		*aPart += *bPart;

		*aPart += overflow;

		overflow = (*aPart < *bPart);
	}

	if (overflow) {
		if (expand(a, 1) == CODE_FAIL) {

			
			return CODE_FAIL;
		}

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

static size_t wordSizeToBits(size_t wordSize) {
	return wordSize * sizeof(word) * 8;
}

void Int_rshUInt(uint* x, size_t shift) {
	if (shift > wordSizeToBits(x->size))
		Int_convertWithSize(x, align_up(shift, sizeof(word) * 8));

	
}

void Int_bitAndUInt(uint* a, uint* b) {
	Int_normalizeSize(a, b);

	for (size_t i = 0; i < MAX(a->size, b->size); i++) {

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