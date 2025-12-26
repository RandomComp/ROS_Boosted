#include "core/math.h"

#include "core/types.h"

#include "core/exception.h"

static bool overflowFlag = false;

bool getOverflowFlag() {
    bool result = overflowFlag;

    overflowFlag = false;

    return result;
}

uint8 fgetCountDecimalPlaces(float x) {
    uint8 result = 0;

    while (fgetFirstNumberAfterDecimalPoint(x) != 0 && result < MAX_FLOAT_STEPS) {
        float oldX = x;

        x *= 10;

        if (x < oldX && !overflowFlag) overflowFlag = true;
        
        result++;
    }

    return result;
}

uint16 getCountDecimalPlaces(double x) {
    uint16 result = 0;

    while (getFirstNumberAfterDecimalPoint(x) != 0 && result < MAX_DOUBLE_STEPS) {
        double oldX = x;

        x *= 10;

        if (x < oldX && !overflowFlag) overflowFlag = true;
        
        result++;
    }

    return result;
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

uint8 getNumberOfDigitsU32(uint32 x) {
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

uint8 getNumberOfDigitsUInt(uint x) {
    
}

uint32 ifloorU32(uint32 x, uint32 align) {
    assert(align != 0, Exception_fromError(DIVISION_BY_ZERO_FATAL_ERROR, Exception_newMessage(__FILE__, __LINE__, "Cannot floor align x with 0.")));

    if (x % align == 0) return x;

    return ((x / align) - 1) * align;
}

uint32 iceilU32(uint32 x, uint32 align) {
    assert(align != 0, Exception_fromError(DIVISION_BY_ZERO_FATAL_ERROR, Exception_newMessage(__FILE__, __LINE__, "Cannot ceil align x with 0.")));

    if (x % align == 0) return x;

    return ((x / align) + 1) * align;
}

uint32 iroundU32(uint32 x, uint32 align) {
    
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

int32 pow32(int16 a, int16 b) {
    if (isPowerOfTwoU32(a)) {

    }

    int32 result = 1;

    b = iabs(b);

    while (b--) {
        int32 oldResult = result;

        result *= a;

        if (result < oldResult && !overflowFlag) overflowFlag = true;
    }

    return result;
}

int64 pow64(int16 a, int16 b) {
    int64 result = 1;

    b = iabs64(b);

    while (b--) {
        int64 oldResult = result;

        result *= a;

        if (result < oldResult && !overflowFlag) overflowFlag = true;
    }

    return result;
}

uint32 powU32(uint16 a, uint16 b) {
    uint32 result = 1;

    while (b--) {
        uint32 oldResult = result;

        result *= a;

        if (result < oldResult && !overflowFlag) overflowFlag = true;
    }

    return result;
}

uint64 powU64(uint16 a, uint16 b) {
    uint64 result = 1;

    while (b--) {
        uint64 oldResult = result;

        result *= a;

        if (result < oldResult && !overflowFlag) overflowFlag = true;
    }

    return result;
}