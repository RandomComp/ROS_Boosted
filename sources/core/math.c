#include "core/types.h"

int64 abs(int64 x) {
    return x < 0 ? -x : x;
}

float fabs(float x) {
    return x < 0.0f ? -x : x;
}

int64 scaleToInteger(float x) {
    
}

uint8 getCountDecimalPlaces(int64 x) {
    
}

uint8 getNumberOfDigits(int64 x) {
    if (x == 0) return 1;

    uint8 result = 0;

    for (; x != 0; result++) x /= 10;
}

float trunc(float x) {
    return (float)((int32)x);
}

float floor(float x) {
    // x >= 0, x E ℤ:   floor(x) = trunc(x)

    // x < 0,  x E ℚ:   floor(x) = -(trunc(|x|) + 1)

    // f(x) = -(|x| + (1 - (|x| - trunc(|x|))))

    if (x < 0 && (fabs(x * 10.0f) % 10 != 0)) return trunc(x) - 1;

    return trunc(x);
}

float ceil(float x) {

}

float round(float x) {

}

int64 pow(int16 a, int16 b) {
    int64 result = 1;

    b = abs(b);

    while (b--) result *= a;

    return result;
}