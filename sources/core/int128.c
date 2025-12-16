#include "core/int128.h"

#include "core/types.h"

#include "core/math.h"

uint128 addUInt128(uint128 a, uint128 b) {
	uint128 result = newUInt128(a.hi, a.lo);

	result.lo += b.lo;

	result.hi += b.hi + (result.lo < b.lo);
	
	return result;
}

uint128 subUInt128(uint128 a, uint128 b) {
	uint128 result = newUInt128(a.hi, a.lo);

	result.lo -= b.lo;

	result.hi -= b.hi - (result.lo > b.lo);

	return result;
}

uint128 mulUInt128(uint128 a, uint128 b) {
	if (isPowerOfTwoU128(b)) {
		return lshUInt128(a, getNumberExponentU128(b, 2));
	}

	uint8 	bLoDigitCount = getNumberOfDigitsU64(b.lo),
			bHiDigitCount = getNumberOfDigitsU64(b.hi);

	uint64 loResult = 0, hiResult = 0;

	for (uint8 i = 0; i < bLoDigitCount; i++) {
		uint64 digitsProductResult = a.lo * getDigitU64(b.lo, i);

		uint64 digitsCount = getNumberOfDigitsU64(digitsProductResult) + i;

		if (digitsCount > 19) {
			hiResult += digitsProductResult * powU64(10, i - 19);
		}

		else loResult += digitsProductResult * powU64(10, i);
	}

	for (uint8 i = 0; i < bHiDigitCount; i++) {
		uint64 digitsProductResult = a.hi * getDigitU64(b.lo, i);

		uint64 digitsCount = getNumberOfDigitsU64(digitsProductResult) + i;

		hiResult += digitsProductResult * powU64(10, i);
	}

	return newUInt128(hiResult, loResult);
}

uint128 divUInt128(uint128 a, uint128 b) {
	uint8 bLoDigitCount = getNumberOfDigitsU64(b.lo);

	uint64 	loResult = 0, hiResult = 0,
			loProduct = a.lo, hiProduct = a.hi;

	uint64 productDigitsCount = getNumberOfDigitsU128(a);

	uint64 digitsProductResult = powU64(2, productDigitsCount);
	
	for (uint8 i = 0; i < productDigitsCount; i++) {
		

	}

	return newUInt128(hiResult, loResult);
}

uint128 bitAndUInt128(uint128 a, uint128 b) {
	uint128 result = newUInt128(0, 0);


}

uint128 bitOrUInt128(uint128 a, uint128 b) {

}