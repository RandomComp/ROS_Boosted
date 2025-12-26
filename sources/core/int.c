#include "core/int.h"

#include "core/types.h"

#include "core/math.h"

uint INT_addUInt(uint a, uint b) { // 0111 1011, 0100 1110
	uint result = a;

	result.lo += b.lo;

	result.hi += b.hi + (result.lo < b.lo); // hi = 1011, lo = 0001 1001, 1100 1001

	
	
	return result;
}

uint INT_subUInt(uint a, uint b) {
	uint result = a;

	result.lo -= b.lo;

	result.hi -= b.hi - (result.lo > b.lo);

	return result;
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
	if (shift >= x.bitDepth) return new();

	if (shift <= 64) {
		x.hi <<= shift; // Сдвиг ненулевых битов для получения свободного пространства для сдвига из lo 0...(shift - 1)

		x.hi |= (x.lo >> (63 - shift)); // Установка битов 64...(64 - shift) из lo в hi часть.
	
		x.lo <<= shift; // Сдвиг и удаление битов из lo 64...(64 - shift).
	}

	else if (shift < 128) {
		INT_lshUInt(x, 64);

		INT_lshUInt(x, shift - 64);
	}
	
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