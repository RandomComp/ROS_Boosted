#ifndef _RANDOM_OS_TYPES_H
#define _RANDOM_OS_TYPES_H

#define true 1

#define false 0

#define far

#define PACKED __attribute__((packed))

#define INT8_MIN (int8)(0x80)

#define INT16_MIN (int16)(0x8000)

#define INT32_MIN (int32)(0x80000000)

#define INT64_MIN (int64)(0x8000000000000000)

#define UINT8_MIN (uint8)(0)

#define UINT16_MIN (uint16)(0)

#define UINT32_MIN (uint32)(0)

#define UINT64_MIN (uint64)(0)

#define INT8_MAX (int8)(0x7F)

#define INT16_MAX (int16)(0x7FFF)

#define INT32_MAX (int32)(0x7FFFFFFF)

#define INT64_MAX (int64)(0x7FFFFFFFFFFFFFFF)

#define UINT8_MAX (uint8)(0xFF)

#define UINT16_MAX (uint16)(0xFFFF)

#define UINT32_MAX (uint32)(0xFFFFFFFF)

#define UINT64_MAX (uint64)(0xFFFFFFFFFFFFFFFF)

#define FLOAT_MIN (double)(1.175494351e-38)

#define DOUBLE_MIN (double)(2.2250738585072014e-308)

#define FLOAT_MAX (double)(3.402823466e+38)

#define DOUBLE_MAX (double)(1.7976931348623158e+308)

#define FLT_EPSILON 1.192092896e-07f

#define FLT_MIN (FLOAT_MIN)

#define DBL_MIN (DOUBLE_MIN)

#define FLT_MAX (FLOAT_MAX)

#define DBL_MAX (DOUBLE_MAX)

#define MAX_FLOAT_STEPS 7

#define MAX_DOUBLE_STEPS 17

#define null 0

#define nullptr 0

#define DEBUG

// Реализация вариативного списка взятого из стэка
typedef struct va_list {
	
} va_list;

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long long uint64;

typedef char int8;
typedef short int16;
typedef int int32;
typedef long long int64;

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;

typedef char int8_t;
typedef short int16_t;
typedef int int32_t;
typedef long long int64_t;

typedef uint8 bool;

typedef unsigned char byte;
typedef unsigned short word;
typedef unsigned int dword;
typedef unsigned long long qword;

#endif