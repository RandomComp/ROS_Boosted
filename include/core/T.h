#ifndef _RANDOM_OS_T_H
#define _RANDOM_OS_T_H

#include "core/types.h"
#include "core/int.h"
#include "core/char.h"
#include "core/string.h"
#include "core/decimal.h"

typedef enum TTypes {
	T_TYPE_SINT,
	
	T_TYPE_UINT,

	T_TYPE_FLOAT,
	T_TYPE_DOUBLE,
	T_TYPE_DECIMAL,

	T_TYPE_CHAR,
	T_TYPE_STRING,
} TTypes;

typedef struct T {
	TTypes type;

	union {
		sint	signedNum;

		uint	unsignedNum;

		float	floatNum;
		double	doubleNum;
		Decimal	decimalNum;

		Char	ch;
		String	str;
	} value;
} T;

inline T T_sintToT(sint x) {
	return (T){.type = T_TYPE_SINT, .value.signedNum = x};
}

inline T T_uintToT(uint x) {
	return (T){.type = T_TYPE_UINT, .value.unsignedNum = x};
}

inline T T_floatToT(float x) {
	return (T){.type = T_TYPE_FLOAT, .value.floatNum = x};
}

inline T T_doubleToT(double x) {
	return (T){.type = T_TYPE_DOUBLE, .value.doubleNum = x};
}

inline T T_decimalToT(Decimal x) {
	return (T){.type = T_TYPE_DOUBLE, .value.decimalNum = x};
}

inline T T_charToT(Char ch) {
	return (T){.type = T_TYPE_CHAR, .value.ch = ch};
}

inline T T_stringToT(String str) {
	return (T){.type = T_TYPE_STRING, .value.str = str};
}

/*
Возвращает T типа uint разрядностью 32 бита
*/
inline T T_new() {
	return T_uintToT(INT_newUInt(32));
}

T addIntWithChar(sint a, Char b);
T addIntWithString(sint a, String b);

T addUIntWithChar(uint a, Char b);
T addUIntWithString(uint a, String b);

T addIntWithT(sint a, T b);
T addUInt32WithT(uint a, T b);

T addCharWithT(Char a, T b);
T addStringWithT(String a, T b);

T T_Add(T a, T b); // Складывание a и b.
T T_Sub(T a, T b); // Вычитание a и b.
T T_Mul(T a, T b); // Умножение a и b.
T T_Div(T a, T b); // Деление a и b.
T T_Mod(T a, T b); // Взятие остатка от деления a и b.

#endif