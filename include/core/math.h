#ifndef _MATH_H
#define _MATH_H

#include "core/types.h"

#define EPSILON 1.192092896e-07f

#define PI 3.1415926535

#define E 2.718281828459

#define MAX_FLOAT_STEPS 7

#define MAX_DOUBLE_STEPS 17

inline int64 iabs64(int64 x) {
    return x < 0 ? -x : x;
}

inline int32 iabs(int32 x) {
    return x < 0 ? -x : x;
}

inline double abs(double x) {
    return x < 0.0 ? -x : x;
}

inline float fabs(float x) {
    return x < 0.0f ? -x : x;
}

inline uint32 getFirstNumber(uint32 x) {
    return iabs(x) % 10;
}

inline uint32 getFirstNumberAfterDecimalPoint(float x) {
    return (uint32)(fabs(frac(x)) * 10.0f) % 10;
}

double mod(double a, double b);

float fmod(float a, float b);

int32 fscaleToInteger(float x);

uint8 fgetCountDecimalPlaces(float x);

int32 scaleToInteger(double x);

uint8 getCountDecimalPlaces(double x);

uint8 getNumberOfDigits(int32 x);

uint8 getNumberOfDigits64(int64 x);

inline double trunc(double x) {
    return (double)((int32)x);
}

inline double frac(double x) {
    return x - trunc(x);
}

inline float ftrunc(float x) {
    return (float)((int32)x);
}

inline float ffrac(float x) {
    return x - ftrunc(x);
}

double floor(double x);
double ceil(double x);
double round(double x);

float ffloor(float x);
float fceil(float x);
float fround(float x);

int32 pow(int16 a, int16 b);

int64 pow64(int16 a, int16 b);

#endif