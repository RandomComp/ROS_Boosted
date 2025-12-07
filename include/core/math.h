#ifndef _MATH_H
#define _MATH_H

#include "core/types.h"

#define PI 3.1415926535

#define E 2.718281828459

int64 abs(int64 x);

float fabs(float x);

float fmod(float a, float b);

int64 scaleToInteger(float x);

uint8 getCountDecimalPlaces(int64 x);

float trunc(float x);

float frac(float x);

float floor(float x);

float ceil(float x);

float round(float x);

int64 pow(int16 a, int16 b);

//float fsinus(uint16 deg);

//float fcosinus(uint16 deg);

#endif