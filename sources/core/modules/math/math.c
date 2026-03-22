#include "core/modules/math/math.h"

#include "core/basic_types.h"

#include "core/modules/exceptions/exception.h"

static ProcessorMathState mathState;

bool getOverflowFlag() {
	bool result = mathState.bOverflow;
	
	mathState.bOverflow = false;

	return result;
}

uint8 fgetCountDecimalPlaces(float x) {
	uint8 result = 0;

	while (fgetFirstNumberAfterDecimalPoint(x) != 0 && result < MAX_FLOAT_STEPS) {
		float oldX = x;

		x *= 10;

		if (x < oldX) mathState.bOverflow = true;
		
		result++;
	}

	return result;
}

uint16 getCountDecimalPlaces(double x) {
	uint16 result = 0;

	while (getFirstNumberAfterDecimalPoint(x) != 0 && result < MAX_DOUBLE_STEPS) {
		double oldX = x;

		x *= 10;

		if (x < oldX) mathState.bOverflow = true;
		
		result++;
	}

	return result;
}

double mod(double a, double b) {
	if (b == 0.0) {
		throw(
			Exception_fromError(
				ERROR_DIVISION_BY_ZERO,
				Format_c_str("Cannot mod [value: dbl] with 0.", a)
			)
		);

		return 0.0;
	}

	return MOD(a, b);
}

float fmod(float a, float b) {
	if (b == 0.0f) {
		throw(
			Exception_fromError(
				ERROR_DIVISION_BY_ZERO,
				Format_c_str("Cannot mod [value: flt] with 0.", a)
			)
		);

		return 0.0f;
	}

	return FMOD(a, b);
}

size_t align_down(size_t x, size_t align) {
	if (align == 0) {
		throw(
			Exception_fromError(
				ERROR_DIVISION_BY_ZERO,
				Format_c_str("Cannot floor align [value: u32] with 0.", x)
			)
		);

		return x;
	}

	if (x % align == 0) return x;

	return (x / align) * align;
}

size_t align_up(size_t x, size_t align) {
	if (align == 0) {
		throw(
			Exception_fromError(
				ERROR_DIVISION_BY_ZERO,
				Format_c_str("Cannot ceil align [value: u32] with 0.", x)
			)
		);

		return x;
	}

	if (x % align == 0) return x;

	return ((x / align) + 1) * align;
}

uint8 getNumberOfDigits32(int32 x) {
	if (x == 0) return 1;

	uint8 result = 0;

	while (getFirstDigit32(x) != 0) {
		x /= 10;
		
		result++;
	}

	return result;
}

uint8 getNumberOfDigits64(int64 x) {
	if (x == 0) return 1;

	uint8 result = 0;

	while (getFirstDigit64(x) != 0) {
		x /= 10;
		
		result++;
	}

	return result;
}

uint8 getNumberOfDigitsU32(size_t x) {
	if (x == 0) return 1;

	uint8 result = 0;

	while (getFirstDigitU32(x) != 0) {
		x /= 10;
		
		result++;
	}

	return result;
}

uint8 getNumberOfDigitsU64(uint64 x) {    
	if (x == 0) return 1;

	uint8 result = 0;

	while (getFirstDigitU64(x) != 0) {
		x /= 10;
		
		result++;
	}

	return result;
}

int32 pow32(int32 a, int32 b) {
	if (b < 0) return 0;

	if (b == 0) return 1;

	if (b == 1) return a;

	int32 result = 1;

	while (--b) {
		int32 oldResult = result;

		result *= a;

		if (result < oldResult) mathState.bOverflow = true;
	}

	return result;
}

size_t powU32(size_t a, size_t b) {
	if (b == 0) return 1;

	if (b == 1) return a;

	size_t result = 1;

	while (b--) {
		size_t oldResult = result;

		result *= a;

		if (result < oldResult) mathState.bOverflow = true;
	}

	return result;
}

int64 pow64(int64 a, int64 b) {
	if (b < 0) return 0;

	if (b == 0) return 1;

	if (b == 1) return a;

	int64 result = 1;

	while (b--) {
		int64 oldResult = result;

		result *= a;

		if (result < oldResult) mathState.bOverflow = true;
	}

	return result;
}

uint64 powU64(uint64 a, uint64 b) {
	if (b == 0) return 1;

	if (b == 1) return a;

	uint64 result = 1;

	while (b--) {
		uint64 oldResult = result;

		result *= a;

		if (result < oldResult) mathState.bOverflow = true;
	}

	return result;
}