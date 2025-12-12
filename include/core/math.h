#ifndef _MATH_H
#define _MATH_H

#include "core/types.h"

#define EPSILON 1.192092896e-07f

#define PI 3.1415926535

#define E 2.718281828459

#define MAX_DOUBLE_STEPS 17

int64 i64abs(int64 x);

int32 iabs(int32 x);

double abs(double x);

double mod(double a, double b);

float fabs(float x);

float fmod(float a, float b);

int32 scaleToInteger(double x);

uint8 getCountDecimalPlaces(double x);

uint8 getNumberOfDigits(int32 x);

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

uint32 getFirstNumberAfterDecimalPoint(float x);

double floor(double x);
double ceil(double x);
double round(double x);

float ffloor(float x);
float fceil(float x);
float fround(float x);

int64 pow(int16 a, int16 b);

#endif