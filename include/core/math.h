#ifndef _MATH_H
#define _MATH_H

#include "core/types.h"

#define EPSILON 1.192092896e-07f

#define PI 3.1415926535

#define E 2.718281828459

int64 abs(int64 x);

double fabs(double x);

double fmod(double a, double b);

int64 scaleToInteger(double x);

uint8 getCountDecimalPlaces(int64 x);

uint8 getNumberOfDigits(int64 x);

double trunc(double x);

double frac(double x);

uint32 getNumberAfterDecimalPoint(double x);

double floor(double x);

double ceil(double x);

double round(double x);

int64 pow(int16 a, int16 b);

#endif