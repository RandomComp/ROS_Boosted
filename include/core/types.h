#ifndef _TYPES_H
#define _TYPES_H

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

#define INT8_MAX (INT8_MIN - 1)

#define INT16_MAX (INT16_MIN - 1)

#define INT32_MAX (INT32_MIN - 1)

#define INT64_MAX (INT64_MIN - 1)

#define UINT8_MAX (uint8)(-1)

#define UINT16_MAX (uint16)(-1)

#define UINT32_MAX (uint32)(-1)

#define UINT64_MAX (uint64)(-1)

typedef unsigned char uint8;

typedef unsigned short uint16;

typedef unsigned int uint32;

typedef unsigned long long uint64;

typedef char int8;

typedef short int16;

typedef int int32;

typedef long long int64;

typedef uint8 bool;

#endif