#include "core/math.h"

#include "core/types.h"

#include "core/fatal_error.h"

int32 iabs(int32 x) {
    return x < 0 ? -x : x;
}

int64 i64abs(int64 x) {
    return x < 0 ? -x : x;
}

double abs(double x) {
    return x < 0.0 ? -x : x;
}

float fabs(float x) {
    return x < 0.0f ? -x : x;
}

double mod(double a, double b) {
    if (b == 0.0) causeFatal(DIVISION_BY_ZERO_FATAL_ERROR);

    return a - (trunc(a / b) * b);
}

float fmod(float a, float b) {
    if (b == 0.0f) causeFatal(DIVISION_BY_ZERO_FATAL_ERROR);

    return a - (ftrunc(a / b) * b);
}

uint8 getCountDecimalPlaces(double x) {
    uint8 result = 0;

    while (getFirstNumberAfterDecimalPoint(x) != 0 && result < MAX_DOUBLE_STEPS) {
        x *= 10;
        
        result++;
    }

    return result;
}

uint8 getNumberOfDigits(int32 x) {
    uint8 result = 0;

    while (getFirstNumber(x) != 0) {
        x /= 10;
        
        result++;
    }

    return result;
}

uint8 getNumberOfDigits(int64 x) {
    if (x == 0) return 1;

    uint8 result = 0;

    for (; x != 0; result++) x /= 10;

    return result;
}

uint32 getFirstNumberAfterDecimalPoint(float x) {
    return (uint32)(fabs(frac(x)) * 10.0f) % 10;
}

uint32 getFirstNumber(uint32 x) {
    return iabs(x) % 10;
}

double floor(double x) {
    double result = trunc(x);

    if (x < 0 && (getFirstNumberAfterDecimalPoint(x) != 0))
        result -= 1;

    return result;
}

double ceil(double x) {
    double result = trunc(x);

    if (x > 0 && (getFirstNumberAfterDecimalPoint(x) != 0))
        result += 1;

    return result;
}

double round(double x) {
    uint32 number = getFirstNumberAfterDecimalPoint(x);

    if (x < 0)
        return  number >= 5 ? floor(x) : ceil(x);

    return      number >= 5 ? ceil(x) : floor(x);
}

float ffloor(float x) {
    float result = ftrunc(x);

    if (x < 0 && (getFirstNumberAfterDecimalPoint(x) != 0))
        result -= 1;

    return result;
}

float fceil(float x) {
    float result = ftrunc(x);

    if (x > 0 && (getFirstNumberAfterDecimalPoint(x) != 0))
        result += 1;

    return result;
}

float fround(float x) {
    uint32 number = getFirstNumberAfterDecimalPoint(x);

    if (x < 0)
        return  number >= 5 ? ffloor(x) : fceil(x);

    return      number >= 5 ? fceil(x) : ffloor(x);
}

int32 pow(int16 a, int16 b) {
    int32 result = 1;

    b = i64abs(b);

    while (b--) result *= a;

    return result;
}

int64 pow64(int16 a, int16 b) {
    int64 result = 1;

    b = i64abs(b);

    while (b--) result *= a;

    return result;
}