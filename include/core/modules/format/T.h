#ifndef _RANDOM_OS_T_H
#define _RANDOM_OS_T_H

#include "core/basic_types.h"
#include "core/int_types.h"
#include "core/types/char_types.h"
#include "core/types/string_types.h"
#include "core/decimal_types.h"

typedef enum T_Types {
	T_TYPE_SINT,
	
	T_TYPE_UINT,

	T_TYPE_FLOAT,
	T_TYPE_DOUBLE,
	T_TYPE_DECIMAL,

	T_TYPE_CHAR,
	T_TYPE_STRING,
} T_Types;

typedef struct T {
	T_Types type;

	union {
		sint8	valueSInt8;
		uint8	valueUInt8;

		sint16	valueSInt16;
		uint16	valueUInt16;

		sint32	valueSInt32;
		uint32	valueUInt32;

		sint64	valueSInt64;
		uint64	valueUInt64;

		sint*	valueSInt;
		uint*	valueUInt;

		float		valueFloat;
		double		valueDouble;
		Decimal*	valueDecimal;

		Char*	ch;
		String*	str;
	} value;
} T;

static inline T T_fromSInt8(sint8 x) {
	return (T){.type = T_TYPE_SINT, .value.valueSInt8 = x};
}

static inline T T_fromUInt8(uint8 x) {
	return (T){.type = T_TYPE_UINT, .value.valueUInt8 = x};
}

static inline T T_fromSInt16(sint16 x) {
	return (T){.type = T_TYPE_SINT, .value.valueSInt16 = x};
}

static inline T T_fromUInt16(uint16 x) {
	return (T){.type = T_TYPE_UINT, .value.valueUInt16 = x};
}

static inline T T_fromSInt32(sint32 x) {
	return (T){.type = T_TYPE_SINT, .value.valueSInt32 = x};
}

static inline T T_fromUInt32(uint32 x) {
	return (T){.type = T_TYPE_UINT, .value.valueUInt32 = x};
}

static inline T T_fromSInt64(sint64 x) {
	return (T){.type = T_TYPE_SINT, .value.valueSInt64 = x};
}

static inline T T_fromUInt64(uint64 x) {
	return (T){.type = T_TYPE_UINT, .value.valueUInt64 = x};
}

static inline T T_fromSInt(sint* x) {
	return (T){.type = T_TYPE_SINT, .value.valueSInt = x};
}

static inline T T_fromUInt(uint* x) {
	return (T){.type = T_TYPE_UINT, .value.valueUInt = x};
}

static inline T T_fromFloatToT(float x) {
	return (T){.type = T_TYPE_FLOAT, .value.floatNum = x};
}

static inline T T_fromDouble(double x) {
	return (T){.type = T_TYPE_DOUBLE, .value.doubleNum = x};
}

static inline T T_fromDecimal(Decimal* x) {
	return (T){.type = T_TYPE_DOUBLE, .value.decimalNum = x};
}

static inline T T_fromChar(Char ch) {
	return (T){.type = T_TYPE_CHAR, .value.ch = ch};
}

static inline T T_fromString(String* str) {
	return (T){.type = T_TYPE_STRING, .value.str = str};
}

/*
Возвращает T типа uint разрядностью 32 бита
*/
static inline T T_new() {
	return T_uintToT(INT_newUInt(32));
}

T addIntWithChar(uinta, Char b);
T addIntWithString(uinta, String b);

T addUIntWithChar(uint a, Char b);
T addUIntWithString(uint a, String b);

T addIntWithT(uinta, T b);
T addUInt32WithT(uint a, T b);

T addCharWithT(Char a, T b);
T addStringWithT(String a, T b);

T T_Add(T a, T b); // Складывание a и b.
T T_Sub(T a, T b); // Вычитание a и b.
T T_Mul(T a, T b); // Умножение a и b.
T T_Div(T a, T b); // Деление a и b.
T T_Mod(T a, T b); // Взятие остатка от деления a и b.

#endif