#include "core/math.h"

#include "core/types.h"

#include "core/fatal_error.h"

double mod(double a, double b) {
    if (b == 0.0) causeFatal(DIVISION_BY_ZERO_FATAL_ERROR);

    return a - (trunc(a / b) * b);
}

float fmod(float a, float b) {
    if (b == 0.0f) causeFatal(DIVISION_BY_ZERO_FATAL_ERROR);

    return a - (ftrunc(a / b) * b);
}

int32 fscaleToInteger(float x) {
    int32 result = x;

    uint8 step = 0;

    while (fgetFirstNumberAfterDecimalPoint(x) != 0 && step < MAX_FLOAT_STEPS) {
        x *= 10;

        result *= 10;
    }

    return result;
}

uint8 fgetCountDecimalPlaces(float x) {
    uint8 result = 0;

    while (fgetFirstNumberAfterDecimalPoint(x) != 0 && result < MAX_FLOAT_STEPS) {
        x *= 10;
        
        result++;
    }

    return result;
}

int64 scaleToInteger(double x) {
    int64 result = 1;

    uint8 step = 0;

    while (getFirstNumberAfterDecimalPoint(x) != 0 && step < MAX_DOUBLE_STEPS) {
        x *= 10;

        result *= 10;
    }

    return result;
}

uint16 getCountDecimalPlaces(double x) {
    uint16 result = 0;

    while (getFirstNumberAfterDecimalPoint(x) != 0 && result < MAX_DOUBLE_STEPS) {
        x *= 10;
        
        result++;
    }

    return result;
}

uint8 getNumberOfDigits32(int32 x) {
    if (x == 0) return 1;

    uint8 result = 0;

    while (getFirstNumber32(x) != 0) {
        x /= 10;
        
        result++;
    }

    return result;
}

uint8 getNumberOfDigits64(int64 x) {    
    if (x == 0) return 1;

    uint8 result = 0;

    while (getFirstNumber64(x) != 0) {
        x /= 10;
        
        result++;
    }

    return result;
}

uint8 getNumberOfDigits32(int32 x) {
    if (x == 0) return 1;

    uint8 result = 0;

    while (getFirstNumberU32(x) != 0) {
        x /= 10;
        
        result++;
    }

    return result;
}

uint8 getNumberOfDigitsU64(uint64 x) {    
    if (x == 0) return 1;

    uint8 result = 0;

    while (getFirstNumberU64(x) != 0) {
        x /= 10;
        
        result++;
    }

    return result;
}

double floor(double x) {
    double result = trunc(x);

    if (x < 0 && (frac(x) != 0))
        result -= 1;

    return result;
}

double ceil(double x) {
    double result = trunc(x);

    if (x > 0 && (frac(x) != 0))
        result += 1;

    return result;
}

double round(double x) {
    if (x < 0)
        return  frac(x) >= 0.5 ? floor(x) : ceil(x);

    return      frac(x) >= 0.5 ? ceil(x) : floor(x);
}

float ffloor(float x) {
    float result = ftrunc(x);

    if (x < 0 && (ffrac(x) != 0))
        result -= 1;

    return result;
}

float fceil(float x) {
    float result = ftrunc(x);

    if (x > 0 && (ffrac(x) != 0))
        result += 1;

    return result;
}

float fround(float x) {
    if (x < 0)
        return  ffrac(x) >= 0.5f ? ffloor(x) : fceil(x);

    return      ffrac(x) >= 0.5f ? fceil(x) : ffloor(x);
}

int32 pow(int16 a, int16 b) {
    int32 result = 1;

    b = iabs(b);

    while (b--) result *= a;

    return result;
}

int64 pow64(int16 a, int16 b) {
    int64 result = 1;

    b = iabs64(b);

    while (b--) result *= a;

    return result;
}