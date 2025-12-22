#ifndef _RANDOM_OS_T_H
#define _RANDOM_OS_T_H

#include "core/types.h"

#include "core/int128.h"

#include "core/char.h"

#include "core/string.h"

typedef enum TTypes {
	T_TYPE_INT8,
	T_TYPE_INT16,
	T_TYPE_INT32,
	T_TYPE_INT64,
	
	T_TYPE_UINT8,
	T_TYPE_UINT16,
	T_TYPE_UINT32,
	T_TYPE_UINT64,
	T_TYPE_UINT128,

	T_TYPE_FLOAT,
	T_TYPE_DOUBLE,

	T_TYPE_CHAR,
	T_TYPE_STRING,
} TTypes;

typedef struct T {
	TTypes type;

	union {
		int8    numX8;
		int16   numX16;
		int32   numX32;
		int64   numX64;

		uint8   numUX8;
		uint16  numUX16;
		uint32  numUX32;
		uint64  numUX64;
		uint128 numUX128;

		float   numFloat;
		double  numDouble;

		Char    ch;
		String  str;
	} value;
} T;

inline T int8ToT(int8 x) {
	return (T){.type = T_TYPE_INT8, .value.numX8 = x};
}

inline T int16ToT(int16 x) {
	return (T){.type = T_TYPE_INT16, .value.numX16 = x};
}

inline T int32ToT(int32 x) {
	return (T){.type = T_TYPE_INT32, .value.numX32 = x};
}

inline T int64ToT(int64 x) {
	return (T){.type = T_TYPE_INT64, .value.numX64 = x};
}

inline T uint8ToT(uint8 x) {
	return (T){.type = T_TYPE_UINT8, .value.numUX8 = x};
}

inline T uint16ToT(uint16 x) {
	return (T){.type = T_TYPE_UINT16, .value.numUX16 = x};
}

inline T uint32ToT(uint32 x) {
	return (T){.type = T_TYPE_UINT32, .value.numUX32 = x};
}

inline T uint64ToT(uint64 x) {
	return (T){.type = T_TYPE_UINT64, .value.numUX64 = x};
}

inline T uint128ToT(uint128 x) {
	return (T){.type = T_TYPE_UINT128, .value.numUX128 = x};
}

inline T floatToT(float x) {
	return (T){.type = T_TYPE_FLOAT, .value.numFloat = x};
}

inline T doubleToT(double x) {
	return (T){.type = T_TYPE_DOUBLE, .value.numDouble = x};
}

inline T charToT(Char ch) {
	return (T){.type = T_TYPE_CHAR, .value.ch = ch};
}

inline T stringToT(String str) {
	return (T){.type = T_TYPE_STRING, .value.str = str};
}

T addInt32WithChar(int32 a, Char b);
T addInt32WithString(int32 a, String b);

T addInt64WithChar(int64 a, Char b);
T addInt64WithString(int64 a, String b);

T addUInt32WithChar(uint32 a, Char b);
T addUInt64WithChar(uint64 a, Char b);
T addUInt32WithString(uint32 a, String b);
T addUInt64WithString(uint64 a, String b);

T addInt32WithT(int32 a, T b);
T addInt64WithT(int64 a, T b);

T addUInt32WithT(uint32 a, T b);
T addUInt64WithT(uint64 a, T b);

T addCharWithT(Char a, T b);
T addStringWithT(String a, T b);

T T_Add(T a, T b); // Складывание a и b.

T T_Sub(T a, T b); // Вычитание a и b.

T T_Mul(T a, T b); // Умножение a и b.

T T_Div(T a, T b); // Деление a и b.

T T_Mod(T a, T b); // Взятие остатка от деления a и b.

#endif