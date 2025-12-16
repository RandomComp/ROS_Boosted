#ifndef _MATH_H
#define _MATH_H

#include "core/types.h"

#include "core/format.h"

#include "core/int128.h"

#include "core/fatal_error.h"

#define EPSILON 1.192092896e-07f

#define PI 3.1415926535

#define E 2.718281828459

#define MAX(a, b) ((a) > (b) ? (a) : (b)) // Небезопасно, лучше использовать нужные inline-функции для вашего типа данных.

#define MIN(a, b) ((a) < (b) ? (a) : (b)) // Небезопасно, лучше использовать нужные inline-функции для вашего типа данных.

#define CLAMP(x, min_value, max_value) (MAX(MIN(x, max_value), min_value)) // Небезопасно, лучше использовать нужные inline-функции для вашего типа данных.

#define ABS(x) ((double)(x) < 0.0 ? -(x) : (x)) // Небезопасно, лучше использовать нужные inline-функции для вашего типа данных.

#define TRUNC(x) ((double)((int64)x)) // Небезопасно, лучше использовать нужные inline-функции для вашего типа данных.

#define FTRUNC(x) ((float)((int32)x)) // Небезопасно, лучше использовать нужные inline-функции для вашего типа данных.

#define MOD(a, b) ((a) - (TRUNC((a) / (b)) * (b))) // Небезопасно, лучше использовать нужные inline-функции для вашего типа данных.

#define FMOD(a, b) ((a) - (FTRUNC((a) / (b)) * (b))) // Небезопасно, лучше использовать нужные inline-функции для вашего типа данных.

#define GET_LAST_DIGIT(x) (uint8)(MOD(ABS(x), 10)) // Небезопасно, лучше использовать нужные inline-функции для вашего типа данных.

bool getOverflowFlag();

inline int32 iabs32(int32 x) {
	return ABS(x);
}

inline int64 iabs64(int64 x) {
	return ABS(x);
}

inline double abs(double x) {
	return ABS(x);
}

inline float fabs(float x) {
	return ABS(x);
}

inline uint32 iminU32(uint32 a, uint32 b) {
	return MIN(a, b);
}

inline uint64 iminU64(uint64 a, uint64 b) {
	return MIN(a, b);
}

inline int32 imin32(int32 a, int32 b) {
	return MIN(a, b);
}

inline int64 imin64(int64 a, int64 b) {
	return MIN(a, b);
}

inline float fmin(float a, float b) {
	return MIN(a, b);
}

inline double min(double a, double b) {
	return MIN(a, b);
}

inline uint32 imaxU32(int32 a, int32 b) {
	return MAX(a, b);
}

inline uint64 imaxU64(int64 a, int64 b) {
	return MAX(a, b);
}

inline int32 imax32(int32 a, int32 b) {
	return MAX(a, b);
}

inline int64 imax64(int64 a, int64 b) {
	return MAX(a, b);
}

inline float fmax(float a, float b) {
	return MAX(a, b);
}

inline double max(double a, double b) {
	return MAX(a, b);
}

inline uint8 getFirstDigit32(int32 x) {
	return GET_LAST_DIGIT(x);
}

inline uint8 getFirstDigit64(int64 x) {
	return GET_LAST_DIGIT(x);
}

inline uint8 getFirstDigitU32(uint32 x) {
	return GET_LAST_DIGIT(x);
}

inline uint8 getFirstDigitU64(uint64 x) {
	return GET_LAST_DIGIT(x);
}

inline uint8 getDigitU32(uint32 x, uint8 digitIndex) {
	return GET_LAST_DIGIT(x / powU32(10, digitIndex));
}

inline uint8 getDigitU64(uint64 x, uint8 digitIndex) {
	return GET_LAST_DIGIT(x / powU64(10, digitIndex));
}

inline uint8 fgetFirstNumberAfterDecimalPoint(float x) {
	return (uint8)(fabs(ffrac(x)) * 10.0f) % 10;
}

inline uint8 getFirstNumberAfterDecimalPoint(double x) {
	return (uint8)(abs(frac(x)) * 10.0) % 10;
}

inline double mod(double a, double b) {
    if (b == 0.0) causeFatal(DIVISION_BY_ZERO_FATAL_ERROR);

    return MOD(a, b);
}

inline float fmod(float a, float b) {
    if (b == 0.0f) causeFatal(DIVISION_BY_ZERO_FATAL_ERROR);

    return FMOD(a, b);
}

inline int32 fscaleToInteger(float x) {
    return x * pow(10, fgetCountDecimalPlaces(x));
}

inline int64 scaleToInteger(double x) {
    return x * pow64(10, getCountDecimalPlaces(x));
}

inline bool isPowerOfTwoU128(uint128 x) {
	return x.lo > 0 && x.lo & (x.lo - 1);
}

inline uint32 getNumberExponentU128(uint128 number, uint32 base) {

}

uint8 fgetCountDecimalPlaces(float x);

uint16 getCountDecimalPlaces(double x);

uint8 getNumberOfDigits32(int32 x);

uint8 getNumberOfDigits64(int64 x);

uint8 getNumberOfDigits128(uint128 x);

uint8 getNumberOfDigitsU32(uint32 x);

uint8 getNumberOfDigitsU64(uint64 x);

uint8 getNumberOfDigitsU128(uint128 x);

inline double trunc(double x) {
	return TRUNC(x);
}

inline double frac(double x) {
	return x - TRUNC(x);
}

inline float ftrunc(float x) {
	return TRUNC(x);
}

inline float ffrac(float x) {
	return x - TRUNC(x);
}

double floor(double x);
double ceil(double x);
double round(double x);

float ffloor(float x);
float fceil(float x);
float fround(float x);

int32 pow32(int16 a, int16 b);
int64 pow64(int16 a, int16 b);

uint32 powU32(uint16 a, uint16 b);
uint64 powU64(uint16 a, uint16 b);

#endif