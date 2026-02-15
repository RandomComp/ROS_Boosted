#ifndef _RANDOM_OS_MATH_H
#define _RANDOM_OS_MATH_H

#include "core/basic_types.h"

// Макросы

#define EPSILON 1.192092896e-07f

#define PI 3.1415926535

#define E 2.718281828459

// Лучше использовать аналогичные функции ( они типобезопаснее, используют эти макросы для упрощения )

#define MAX(a, b) ((a) > (b) ? (a) : (b))

#define MIN(a, b) ((a) < (b) ? (a) : (b))

#define CLAMP(x, min_value, max_value) (MAX(MIN(x, max_value), min_value))

#define INRANGE(value, min_value, max_value) ((value) >= (min_value) && (value) <= (max_value))

#define IABS(x) (x < 0 ? -(x) : (x))

#define FABS(x) ((float)(x) < 0.0f ? -(x) : (x))

#define ABS(x) ((double)(x) < 0.0 ? -(x) : (x))

#define FTRUNC(x) ((float)((int32)x))

#define TRUNC(x) ((double)((int64)x))

#define MOD(a, b) ((a) - (TRUNC((a) / (b)) * (b)))

#define FMOD(a, b) ((a) - (FTRUNC((a) / (b)) * (b)))

#define GET_FIRST_DIGIT(x) (uint8)(MOD(ABS(x), 10))

typedef struct ProcessorMathState {
	bool bOverflow; // Флаг переполнения типа
	size_t divRem; // Остаток от деления, вычисленный при вычислении деления
} ProcessorMathState;

bool getOverflowFlag();

int32 pow32(int32 a, int32 b);
int64 pow64(int64 a, int64 b);

size_t powU32(size_t a, size_t b);
uint64 powU64(uint64 a, uint64 b);

static inline int32 abs32(int32 x) {
	return IABS(x);
}

static inline int64 abs64(int64 x) {
	return IABS(x);
}

static inline float fabs(float x) {
	return FABS(x);
}

static inline double abs(double x) {
	return ABS(x);
}

static inline size_t minU32(size_t a, size_t b) {
	return MIN(a, b);
}

static inline uint64 minU64(uint64 a, uint64 b) {
	return MIN(a, b);
}

static inline int32 min32(int32 a, int32 b) {
	return MIN(a, b);
}

static inline int64 min64(int64 a, int64 b) {
	return MIN(a, b);
}

static inline float fmin(float a, float b) {
	return MIN(a, b);
}

static inline double min(double a, double b) {
	return MIN(a, b);
}

static inline size_t maxU32(size_t a, size_t b) {
	return MAX(a, b);
}

static inline uint64 maxU64(uint64 a, uint64 b) {
	return MAX(a, b);
}

static inline int32 max32(int32 a, int32 b) {
	return MAX(a, b);
}

static inline int64 max64(int64 a, int64 b) {
	return MAX(a, b);
}

static inline float fmax(float a, float b) {
	return MAX(a, b);
}

static inline double max(double a, double b) {
	return MAX(a, b);
}

static inline size_t clampU32(size_t x, size_t min, size_t max) {
	return CLAMP(x, min, max);
}

static inline uint64 clampU64(uint64 x, uint64 min, uint64 max) {
	return CLAMP(x, min, max);
}

static inline int32 clamp32(int32 x, int32 min, int32 max) {
	return CLAMP(x, min, max);
}

static inline int64 clamp64(int64 x, int64 min, int64 max) {
	return CLAMP(x, min, max);
}

static inline float fclamp(float x, float min, float max) {
	return CLAMP(x, min, max);
}

static inline double clamp(double x, double min, double max) {
	return CLAMP(x, min, max);
}

static inline bool inRangeU8(uint8 x, uint8 min, uint8 max) {
	return INRANGE(x, min, max);
}

static inline bool inRangeU16(uint16 x, uint16 min, uint16 max) {
	return INRANGE(x, min, max);
}

static inline bool inRangeU32(size_t x, size_t min, size_t max) {
	return INRANGE(x, min, max);
}

static inline bool inRangeU64(uint64 x, uint64 min, uint64 max) {
	return INRANGE(x, min, max);
}

static inline bool inRange8(int8 x, int8 min, int8 max) {
	return INRANGE(x, min, max);
}

static inline bool inRange16(int16 x, int16 min, int16 max) {
	return INRANGE(x, min, max);
}

static inline bool inRange32(int32 x, int32 min, int32 max) {
	return INRANGE(x, min, max);
}

static inline bool inRange64(int64 x, int64 min, int64 max) {
	return INRANGE(x, min, max);
}

static inline bool finRange(float x, float min, float max) {
	return INRANGE(x, min, max);
}

static inline bool inRange(double x, double min, double max) {
	return INRANGE(x, min, max);
}

static inline uint8 getFirstDigit32(int32 x) {
	return GET_FIRST_DIGIT(x);
}

static inline uint8 getFirstDigit64(int64 x) {
	return GET_FIRST_DIGIT(x);
}

static inline uint8 getFirstDigitU32(size_t x) {
	return GET_FIRST_DIGIT(x);
}

static inline uint8 getFirstDigitU64(uint64 x) {
	return GET_FIRST_DIGIT(x);
}

static inline uint8 getDigitU32(size_t x, uint8 digitIndex) {
	return GET_FIRST_DIGIT(x / powU32(10, digitIndex));
}

static inline uint8 getDigitU64(uint64 x, uint8 digitIndex) {
	return GET_FIRST_DIGIT(x / powU64(10, digitIndex));
}

static inline double trunc(double x) {
	return TRUNC(x);
}

static inline float ftrunc(float x) {
	return TRUNC(x);
}

static inline double frac(double x) {
	return x - TRUNC(x);
}

static inline float ffrac(float x) {
	return x - TRUNC(x);
}

static inline uint8 fgetFirstNumberAfterDecimalPoint(float x) {
	return (uint8)(fabs(ffrac(x)) * 10.0f) % 10;
}

static inline uint8 getFirstNumberAfterDecimalPoint(double x) {
	return (uint8)(abs(frac(x)) * 10.0) % 10;
}

double mod(double a, double b);

float fmod(float a, float b);

uint8 fgetCountDecimalPlaces(float x);

uint16 getCountDecimalPlaces(double x);

static inline int32 fscaleToInteger(float x) {
	if (x == 0.0f) return 0;

	return x * pow64(10, fgetCountDecimalPlaces(x));
}

static inline int64 scaleToInteger(double x) {
	if (x == 0.0f) return 0;

	return x * pow64(10, getCountDecimalPlaces(x));
}

static inline bool isPowerOfTwoU32(size_t x) {
	return x > 0 && (x & (x - 1) == 0);
}

uint8 getNumberOfDigits32(int32 x);

uint8 getNumberOfDigits64(int64 x);

uint8 getNumberOfDigitsU32(size_t x);

uint8 getNumberOfDigitsU64(uint64 x);

size_t floorU32(size_t x, size_t align);

size_t ceilU32(size_t x, size_t align);

size_t roundU32(size_t x, size_t align);

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

#endif