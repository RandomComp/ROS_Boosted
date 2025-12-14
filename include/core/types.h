#ifndef _TYPES_H
#define _TYPES_H

#include "charset/ugsm.h"

#include "charset/ascii.h"

#include "drivers/low-level/base/mem.h"

#include "core/format.h"

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

#define FLOAT_MIN 1.175494351e-38f

#define DOUBLE_MIN 2.2250738585072014e-308

#define FLOAT_MAX 3.402823466e+38f

#define DOUBLE_MAX 1.7976931348623158e+308f

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

typedef struct Decimal {
	int32 numerator;

	int32 denominator;
} Decimal;

typedef enum Charset {
	CHARSET_UGSM,
	CHARSET_ASCII,
} Charset;

typedef union CharUnion {
	UGSMGlyphCode   UGSMChar;
	
	int8            ASCIIChar;
} CharUnion;

typedef struct Char {
	Charset charset;

	CharUnion ch;
} Char;

typedef struct String {
	uint32 length;

	MemoryRegion* region;
} String;

typedef enum TTypes {
	T_TYPE_INT8,
	T_TYPE_INT16,
	T_TYPE_INT32,
	T_TYPE_INT64,
	
	T_TYPE_UINT8,
	T_TYPE_UINT16,
	T_TYPE_UINT32,
	T_TYPE_UINT64,

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

inline CharUnion newCharUnionFromASCII(int8 ch) {
	return (CharUnion){.ASCIIChar = ch};
}

inline CharUnion newCharUnionFromUGSM(UGSMGlyphCode ch) {
	return (CharUnion){.UGSMChar = ch};
}

inline Char newCharFromASCII(int8 ch) {
	return (Char){.charset = CHARSET_ASCII, .ch = newCharUnionFromASCII(ch)};
}

inline Char newCharFromUGSM(UGSMGlyphCode ch) {
	return (Char){.charset = CHARSET_UGSM, .ch = newCharUnionFromUGSM(ch)};
}

inline String newString(uint32 length) {
	MemoryRegion* charMem = malloc(sizeof(Char) * length, MEMORY_ACCESS_READ | MEMORY_ACCESS_WRITE);
	
	return (String){.length = length, .region = charMem};
}

inline String newStringFromASCII(ASCIIGlyphCode* str) {
	uint32 length = ASCIIgetLength(str);

	String result = newString(length);

	memcpy(result.region->memory, str, length);
	
	return result;
}

inline String newStringFromUGSM(UGSMGlyphCode* str) {
	uint32 length = UGSMgetLength(str);

	String result = newString(length);

	memcpy(result.region->memory, str, length);
	
	return result;
}

inline Char* getCharArrayFromString(String str) {
	return (Char*)str.region->memory;
}

inline CharUnion charUnionFromUGSMChar(UGSMGlyphCode code) {
	return (CharUnion){.UGSMChar = code};
}

inline CharUnion charUnionFromASCIIChar(int8 code) {
	return (CharUnion){.ASCIIChar = code};
}

inline Char charCharsetToASCII(Char ch) {
	ASCIIGlyphCode result = ASCII_CHAR_NULL;

	if (ch.charset == CHARSET_ASCII)
		result = ch.ch.ASCIIChar;

	else if (ch.charset == CHARSET_UGSM)
		result = ASCIIUGSMCharToASCII(ch.ch.UGSMChar);

	return newCharFromASCII(result);
}

inline Char charCharsetToUGSM(Char ch) {
	UGSMGlyphCode result = UGSM_CHAR_NULL;

	if (ch.charset == CHARSET_ASCII)
		result = UGSMASCIICharToUGSM(ch.ch.ASCIIChar);

	else if (ch.charset == CHARSET_UGSM)
		result = ch.ch.UGSMChar;

	return newCharFromUGSM(result);
}

inline Char digitToChar(uint8 digit) {
	return newCharFromUGSM(UGSMdigitToUGSM(digit));
}

inline String charToString(Char ch) {
	String result = newString(1);

	setCharToString(&result, 0, ch);

	return result;
}

inline void freeString(String* str) {
	if (str != null && str->region != null) {
		free(str->region);

		str->region = null;
	}

	// TODO: handle error
}

void setCharToString(String* str, uint32 index, Char ch);

Char getCharFromString(String* str, uint32 index);

String int64ToString(int64 x);

String uint64ToString(uint64 x);

String int32ToString(int32 x);

String uint32ToString(uint32 x);

String stringConcatenate(String a, String b); // Конкатенирует две строки

String stringFromT(T x);

T addInt32WithChar(int32 a, Char b);

T addInt32WithString(int32 a, String b);

T addUInt32WithChar(uint32 a, Char b);

T addUInt32WithString(uint32 a, String b);

T addInt64WithChar(int32 a, Char b);

T addInt64WithString(int32 a, String b);

T addUInt64WithChar(uint32 a, Char b);

T addUInt64WithString(uint32 a, String b);

T addInt32WithT(int32 a, T b);

T addUInt32WithT(int32 a, T b);

T addInt64WithT(int32 a, T b);

T addUInt64WithT(int32 a, T b);

T addCharWithT(Char a, T b);

T addStringWithT(String a, T b);

T T_Add(T a, T b); // Складывание a и b.

T T_Sub(T a, T b); // Вычитание a и b.

T T_Mul(T a, T b); // Умножение a и b.

T T_Div(T a, T b); // Деление a и b.

T T_Mod(T a, T b); // Взятие остатка от деления a и b.

double doubleFromDecimal(Decimal decimal);

Decimal doubleToDecimal(double x);

#endif