#include "core/int.h"

#include "core/types.h"

#include "core/math.h"

uint addUInt(uint a, uint b) { // 0111 1011, 0100 1110
	uint result = a;

	result.lo += b.lo;

	result.hi += b.hi + (result.lo < b.lo); // hi = 1011, lo = 0001 1001, 1100 1001

	
	
	return result;
}

uint subUInt(uint a, uint b) {
	uint result = a;

	result.lo -= b.lo;

	result.hi -= b.hi - (result.lo > b.lo);

	return result;
}


uint mulUInt(uint a, uint b) {
	uint result = getUIntZero();

	

	result = addUInt(result, newUInt(0, a.lo * b.lo));

	result = addUInt(result, lshUInt(newUInt128(0, a.hi * b.lo), 64));

	result = addUInt(result, newUInt(0, a.lo * b.hi));

	result = addUInt(result, lshUInt(newUInt128(0, a.hi * b.hi), 64));

	// 11111111111111111111111111111111111111111111111111111111111111100000000000000000000000000000000000000000000000000000000000000001
	
	// 11111111111111111111111111111111111111111111111111111111111111010000000000000000000000000000000000000000000000000000000000000001

	// for (uint8 i = 0; i < 128; i++) {
	// 	if (checkBitU128(b, i)) {
	// 		result = addUInt128(result, lshUInt128(a, i));
	// 	}
	// }

	return result;
}

uint divUInt(uint a, uint b) {
	uint8 bLoDigitCount = getNumberOfDigitsU64(b.lo);

	uint result = rshUInt(mulUInt(a, newUInt128(0, 0x1000ULL / b.lo)), 12);

	return result;
}

uint lshUInt(uint x, uint8 shift) {
	if (shift >= 128) return getUIntZero();

	if (shift <= 64) {
		x.hi <<= shift; // Сдвиг ненулевых битов для получения свободного пространства для сдвига из lo 0...(shift - 1)

		x.hi |= (x.lo >> (63 - shift)); // Установка битов 64...(64 - shift) из lo в hi часть.
	
		x.lo <<= shift; // Сдвиг и удаление битов из lo 64...(64 - shift).
	}

	else if (shift < 128) {
		x = lshUInt(lshUInt(x, 64), shift - 64);
	}
	
	return x;
}

uint rshUInt(uint x, uint8 shift) {
	if (shift >= 128) return getUIntZero();

	if (shift <= 64) {
		x.lo >>= shift; // Сдвиг ненулевых битов для получения свободного пространства для сдвига из lo (shift - 1)...0
		
		x.lo |= (x.hi & makeIdentityMaskForU64(shift)) << (63 - shift); // Установка битов (shift - 1)...0 из hi в lo часть 64...(64 - shift).
		
		x.hi >>= shift; // Сдвиг и удаление битов из hi (shift - 1)...0.
	}

	else if (shift < 128) {
		x = rshUInt(rshUInt(x, 64), shift - 64);
	}
	
	return x;
}