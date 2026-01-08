#ifndef _RANDOM_OS_MATH_H
#define _RANDOM_OS_MATH_H

#include "core/types/basic_types.h"

#include "core/types/high-level/int_types.h"

#include "core/types/low-level/error_types.h"

// Макросы

#define EPSILON 1.192092896e-07f

#define PI 3.1415926535

#define E 2.718281828459

#define MAX(a, b) ((a) > (b) ? (a) : (b)) // Небезопасно, лучше использовать нужные inline-функции для вашего типа данных.

#define MIN(a, b) ((a) < (b) ? (a) : (b)) // Небезопасно, лучше использовать нужные inline-функции для вашего типа данных.

#define CLAMP(x, min_value, max_value) (MAX(MIN(x, max_value), min_value)) // Небезопасно, лучше использовать нужные inline-функции для вашего типа данных.

#define TRUNC(x) ((double)((int64)x)) // Небезопасно, лучше использовать нужные inline-функции для вашего типа данных.

#define FTRUNC(x) ((float)((int32)x)) // Небезопасно, лучше использовать нужные inline-функции для вашего типа данных.

#define MOD(a, b) ((a) - (TRUNC((a) / (b)) * (b))) // Небезопасно, лучше использовать нужные inline-функции для вашего типа данных.

#define FMOD(a, b) ((a) - (FTRUNC((a) / (b)) * (b))) // Небезопасно, лучше использовать нужные inline-функции для вашего типа данных.

typedef struct ProcessorMathState {
	bool bOverflow; // Флаг переполнения типа
	uint32 divRem; // Остаток от деления, вычисленный при вычислении деления
} ProcessorMathState;

bool getOverflowFlag();

static inline int32 iabs32(int32 x) {
	return x < 0 ? -x : x;
}

static inline int64 iabs64(int64 x) {
	return x < 0 ? -x : x;
}

static inline double abs(double x) {
	return x < 0 ? -x : x;
}

static inline float fabs(float x) {
	return x < 0 ? -x : x;
}

static inline uint32 iminU32(uint32 a, uint32 b) {
	return MIN(a, b);
}

static inline uint64 iminU64(uint64 a, uint64 b) {
	return MIN(a, b);
}

static inline int32 imin32(int32 a, int32 b) {
	return MIN(a, b);
}

static inline int64 imin64(int64 a, int64 b) {
	return MIN(a, b);
}

static inline float fmin(float a, float b) {
	return MIN(a, b);
}

static inline double min(double a, double b) {
	return MIN(a, b);
}

static inline uint32 imaxU32(int32 a, int32 b) {
	return MAX(a, b);
}

static inline uint64 imaxU64(int64 a, int64 b) {
	return MAX(a, b);
}

static inline int32 imax32(int32 a, int32 b) {
	return MAX(a, b);
}

static inline int64 imax64(int64 a, int64 b) {
	return MAX(a, b);
}

static inline float fmax(float a, float b) {
	return MAX(a, b);
}

static inline double max(double a, double b) {
	return MAX(a, b);
}

static inline int32 getFirstDigit32(int32 x) {
	return x % 10;
}

static inline int64 getFirstDigit64(int64 x) {
	return x % 10;
}

static inline uint32 getFirstDigitU32(uint32 x) {
	return x % 10;
}

static inline uint64 getFirstDigitU64(uint64 x) {
	return x % 10;
}

static inline uint32 getDigitU32(uint32 x, uint8 digitIndex) {
	return getFirstDigitU32(x / powU32(10, digitIndex));
}

static inline uint64 getDigitU64(uint64 x, uint8 digitIndex) {
	return getFirstDigitU64(x / powU64(10, digitIndex));
}

static inline uint32 fgetFirstNumberAfterDecimalPoint(float x) {
	return getFirstDigitU32(fabs(ffrac(x)) * 10.0f);
}

static inline uint64 getFirstNumberAfterDecimalPoint(double x) {
	return getFirstDigitU64(abs(frac(x)) * 10.0);
}

static inline double mod(double a, double b) {
    assert(b != 0.0, Exception_fromError(ERROR_DIVISION_BY_ZERO, Exception_messageFromString("Cannot mod [dbl] with 0.", a)));

    return MOD(a, b);
}

static inline float fmod(float a, float b) {
    if (b == 0.0f) causeFatal(DIVISION_BY_ZERO_FATAL_ERROR);

    return FMOD(a, b);
}

static inline int32 fscaleToInteger(float x) {
    return x * pow(10, fgetCountDecimalPlaces(x));
}

static inline int64 scaleToInteger(double x) {
    return x * pow64(10, getCountDecimalPlaces(x));
}

static inline bool isPowerOfTwoU32(uint32 x) {
	return x > 0 && (x & (x - 1) == 0);
}

static inline bool isPowerOfTwoUInt(uint x) {
	return bigThanUInt(x, getUIntZero()) && equalUInt(bitAndUInt(x, subUInt(x, getUIntOne())), getUIntZero());
}

static inline uint32 logUInt(uint number, uint32 base) {
	
}

uint8 fgetCountDecimalPlaces(float x);

uint16 getCountDecimalPlaces(double x);

uint8 getNumberOfDigits32(int32 x);

uint8 getNumberOfDigits64(int64 x);

uint8 getNumberOfDigitsU32(uint32 x);

uint8 getNumberOfDigitsU64(uint64 x);

uint8 getNumberOfDigitsUInt(uint x);

static inline uint32 ifloorU32(uint32 x, uint32 align) {
	assert(align != 0, Exception_fromError(ERROR_DIVISION_BY_ZERO, Exception_newMessage(__FILE__, __LINE__, "Cannot floor align x with 0.")));

	if (x % align == 0) return x;

	return ((x / align) - 1) * align;
}

static inline uint32 iceilU32(uint32 x, uint32 align) {
	assert(align != 0, Exception_fromError(ERROR_DIVISION_BY_ZERO, Exception_messageFromString("Cannot ceil align x with 0.")));

	if (x % align == 0) return x;

	return ((x / align) + 1) * align;
}

static inline uint32 iroundU32(uint32 x, uint32 align) {
    
}

static inline double trunc(double x) {
	return TRUNC(x);
}

static inline double frac(double x) {
	return x - TRUNC(x);
}

static inline float ftrunc(float x) {
	return TRUNC(x);
}

static inline float ffrac(float x) {
	return x - TRUNC(x);
}

static inline double floor(double x) {
    double result = trunc(x);

    if (x < 0 && (frac(x) != 0))
        result -= 1;

    return result;
}

static inline double ceil(double x) {
    double result = trunc(x);

    if (x > 0 && (frac(x) != 0))
        result += 1;

    return result;
}

static inline double round(double x) {
    if (x < 0)
        return  frac(x) >= 0.5 ? floor(x) : ceil(x);

    return      frac(x) >= 0.5 ? ceil(x) : floor(x);
}

static inline float ffloor(float x) {
    float result = ftrunc(x);

    if (x < 0 && (ffrac(x) != 0))
        result -= 1;

    return result;
}

static inline float fceil(float x) {
    float result = ftrunc(x);

    if (x > 0 && (ffrac(x) != 0))
        result += 1;

    return result;
}

static inline float fround(float x) {
    if (x < 0)
        return  ffrac(x) >= 0.5f ? ffloor(x) : fceil(x);

    return      ffrac(x) >= 0.5f ? fceil(x) : ffloor(x);
}

int32 pow32(int16 a, int16 b);
int64 pow64(int16 a, int16 b);

uint32 powU32(uint16 a, uint16 b);
uint64 powU64(uint16 a, uint16 b);

#endif