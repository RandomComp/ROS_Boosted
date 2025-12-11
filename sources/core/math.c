#include "core/math.h"

#include "core/types.h"

#include "core/fatal_error.h"

int64 abs(int64 x) {
    return x < 0 ? -x : x;
}

double fabs(double x) {
    return x < 0.0f ? -x : x;
}

double fmod(double a, double b) {
    if (b == 0.0f) causeFatal(DivisionByZeroError);

    return a - (trunc(a / b) * b);
}

int64 scaleToInteger(double x) {
    
}

uint8 getCountDecimalPlaces(int64 x) {
    
}

uint8 getNumberOfDigits(int64 x) {
    if (x == 0) return 1;

    uint8 result = 0;

    for (; x != 0; result++) x /= 10;

    return result;
}

double trunc(double x) {
    return (double)((int32)x);
}

double frac(double x) {
    return x - trunc(x);
}

uint32 getNumberAfterDecimalPoint(double x) {
    return (uint32)(fabs(frac(x)) * 10.0f) % 10;
}

double floor(double x) {
    double result = trunc(x);

    if (x < 0 && (getNumberAfterDecimalPoint(x) != 0))
        result -= 1;

    return result;
}

double ceil(double x) {
    double result = trunc(x);

    if (x > 0 && getNumberAfterDecimalPoint(x) != 0)
        result += 1;

    return result;
}

double round(double x) {
    uint32 number = getNumberAfterDecimalPoint(x);

    if (x < 0)
        return  number >= 5 ? floor(x) : ceil(x);

    return      number >= 5 ? ceil(x) : floor(x);
}

int64 pow(int16 a, int16 b) {
    int64 result = 1;

    b = abs(b);

    while (b--) result *= a;

    return result;
}