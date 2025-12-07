#include "core/types.h"

#include "core/fatal_error.h"

int64 abs(int64 x) {
    return x < 0 ? -x : x;
}

float fabs(float x) {
    return x < 0.0f ? -x : x;
}

float fmod(float a, float b) {
    if (b == 0) causeFatal(DivisionByZeroError);

    return a - (trunc(a / b) * b);
}

int64 scaleToInteger(float x) {
    
}

uint8 getCountDecimalPlaces(int64 x) {
    
}

uint8 getNumberOfDigits(int64 x) {
    if (x == 0) return 1;

    uint8 result = 0;

    for (; x != 0; result++) x /= 10;

    return result;
}

float trunc(float x) {
    return (float)((int32)x);
}

float frac(float x) {
    return fabs(x - trunc(x));
}

uint32 getNumberAfterDecimalPoint(float x) {
    return (uint32)(frac(x) * 10.0f) % 10;
}

float floor(float x) {
    float result = trunc(x);

    if (x < 0 && (getNumberAfterDecimalPoint(x) != 0))
        result -= 1;

    return result;
}

float ceil(float x) {
    float result = trunc(x);

    if (x > 0 && getNumberAfterDecimalPoint(x) != 0)
        result += 1;

    return result;
}

float round(float x) {
    uint32 number = getNumberAfterDecimalPoint(x);

    if (x < 0) return number >= 5 ? floor(x) : ceil(x);

    return number >= 5 ? ceil(x) : floor(x);
}

int64 pow(int16 a, int16 b) {
    int64 result = 1;

    b = abs(b);

    while (b--) result *= a;

    return result;
}