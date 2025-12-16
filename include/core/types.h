#ifndef _RANDOM_OS_TYPES_H
#define _RANDOM_OS_TYPES_H

#define true 1

#define false 0

#define far

#define PACKED __attribute__((packed))

#define INT8_MIN (int8)(1 << (8 - 1))

#define INT16_MIN (int16)(1 << (16 - 1))

#define INT32_MIN (int32)(1 << (32 - 1))

#define INT64_MIN (int64)(1 << (64 - 1))

#define UINT8_MIN 0

#define UINT16_MIN 0

#define UINT32_MIN 0

#define UINT64_MIN 0

#define INT8_MAX 0xFFL

#define INT16_MAX 0xFFFFL

#define INT32_MAX 0xFFFFFFFFL

#define INT64_MAX 0xFFFFFFFFFFFFFFFFLL

#define UINT8_MAX 0xFFU

#define UINT16_MAX 0xFFFFU

#define UINT32_MAX 0xFFFFFFFFU

#define UINT64_MAX 0xFFFFFFFFFFFFFFFFULL

#define FLOAT_MIN 1.175494351e-38f

#define DOUBLE_MIN 2.2250738585072014e-308

#define FLOAT_MAX 3.402823466e+38f

#define DOUBLE_MAX 1.7976931348623158e+308f

#define MAX_FLOAT_STEPS 7

#define MAX_DOUBLE_STEPS 17

typedef unsigned char uint8;

typedef unsigned short uint16;

typedef unsigned int uint32;

typedef unsigned long long uint64;

typedef char int8;

typedef short int16;

typedef int int32;

typedef long long int64;

typedef uint8 bool;

#define null 0

#endif