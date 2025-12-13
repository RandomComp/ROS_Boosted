#include "core/types.h"

#include "core/math.h"

void setCharToString(String* str, uint32 index, Char ch) {
	if (str == null); // TODO: handle error

	Char* charArray = getCharArrayFromString(*str);

	if (charArray == null); // TODO: handle error

	charArray[index] = ch;
}

Char getCharFromString(String* str, uint32 index) {
	if (str == null); // TODO: handle error

	Char* charArray = getCharArrayFromString(*str);

	if (charArray == null); // TODO: handle error

	return charArray[index];
}

String int64ToString(int64 x) {
	String result = newString(getNumberOfDigits64(x));

	setCharToString(&result, 0, newChar(charUnionFromUGSMChar(UGSM_CHAR_0)));

	uint32 index = 0;

	while (x != 0) {
		Char ch = newChar(charUnionFromUGSMChar(UGSMASCIICharToUGSM(getFirstNumber64(x))));

		setCharToString(&result, result.length - index, ch);

		x /= 10;

		index++;
	}

	return result;
}

String uint64ToString(uint64 x) {
	String result = newString(getNumberOfDigitsU64(x));

	setCharToString(&result, 0, newChar(charUnionFromUGSMChar(UGSM_CHAR_0)));

	uint32 index = 0;

	while (x != 0) {
		Char ch = newChar(charUnionFromUGSMChar(UGSMASCIICharToUGSM(getFirstNumberU64(x))));

		setCharToString(&result, result.length - index, ch);

		x /= 10;

		index++;
	}

	return result;
}

String int32ToString(int32 x) {

}

String uint32ToString(uint32 x) {

}

String charToString(Char x) {

}

String stringConcatenate(String a, String b) {
	String result = newString(a.length + b.length);

	memcpy(result.region->memory, a.region->memory, a.length);

	memcpy((void*)((uint32)result.region->memory + a.length + 1), b.region->memory, b.length);

	return result;
}

String stringFromT(T x) {
	switch (x.type) {
		case T_TYPE_INT8:   return int32ToString((int32)x.value.numX8);
		case T_TYPE_INT16:  return int32ToString((int32)x.value.numX16);
		case T_TYPE_INT32:  return int32ToString(x.value.numX32);
		
		case T_TYPE_UINT8:  return uint32ToString((uint32)x.value.numUX8);
		case T_TYPE_UINT16: return uint32ToString((uint32)x.value.numUX16);
		case T_TYPE_UINT32: return uint32ToString(x.value.numUX32);

		case T_TYPE_INT64:  return int64ToString(x.value.numX64);
		case T_TYPE_UINT64: return uint64ToString(x.value.numUX64);

		case T_TYPE_CHAR:   return charToString(x.value.ch);
		case T_TYPE_STRING: return x.value.str;
	}

	//warn(UNKNOWN_T_TYPE_WARNING);

	String defaultResult = newString(1);

	setCharToString(&defaultResult, 0, )

	return defaultResult;
}

T addInt32WithChar(int32 a, Char b) {
	CharUnion result = b.ch;

	if (b.charset == CHARSET_ASCII)
		result.ASCIIChar = (result.ASCIIChar + a) % 0xff;

	else if (b.charset == CHARSET_UGSM)
		result.UGSMChar = (result.UGSMChar + a) % 0xffff;
	
	return charToT(newChar(result));
}

T addInt32WithString(int32 a, String b) {
	return stringToT(stringConcatenate(int32ToString(a), b));
}

T addUInt32WithChar(uint32 a, Char b) {
	CharUnion result = b.ch;

	if (b.charset == CHARSET_ASCII)
		result.ASCIIChar = (result.ASCIIChar + a) % 0xff;

	else if (b.charset == CHARSET_UGSM)
		result.UGSMChar = (result.UGSMChar + a) % 0xffff;
	
	return charToT(newChar(result));
}

T addUInt32WithString(uint32 a, String b) {
	return stringToT(stringConcatenate(uint32ToString(a), b));
}

T addInt32WithT(int32 a, T b) {
	switch (b.type) {
		case T_TYPE_INT8: return int32ToT(a + (int32)b.value.numX8);
		case T_TYPE_INT16: return int32ToT(a + (int32)b.value.numX16);
		case T_TYPE_INT32: return int32ToT(a + b.value.numX32);
		case T_TYPE_INT64: return int32ToT((int64)a + b.value.numX64);
		case T_TYPE_UINT8: return int32ToT(a + (uint32)b.value.numUX8);
		case T_TYPE_UINT16: return int32ToT(a + (uint32)b.value.numUX16);
		case T_TYPE_UINT32: return int32ToT(a + (uint32)b.value.numUX32);
		case T_TYPE_UINT64: return int32ToT((int64)a + (int64)b.value.numUX64); // TODO: Добавить uint128/int128, и использовать вместо приведения uint64 к int64 ( возможно переполнение )
		case T_TYPE_CHAR: return addInt32WithChar(a, b.value.ch);
		case T_TYPE_STRING: return addInt32WithString(a, b.value.str);
	}
}

T addUInt32WithT(int32 a, T b) {
	switch (b.type) {
		case T_TYPE_INT8: return uint32ToT(a + (int32)b.value.numX8);
		case T_TYPE_INT16: return uint32ToT(a + (int32)b.value.numX16);
		case T_TYPE_INT32: return uint32ToT(a + b.value.numX32);
		case T_TYPE_INT64: return uint32ToT((int64)a + b.value.numX64);
		case T_TYPE_UINT8: return uint32ToT(a + (uint32)b.value.numUX8);
		case T_TYPE_UINT16: return uint32ToT(a + (uint32)b.value.numUX16);
		case T_TYPE_UINT32: return uint32ToT(a + (uint32)b.value.numUX32);
		case T_TYPE_UINT64: return uint32ToT((int64)a + (int64)b.value.numUX64); // TODO: Добавить uint128/int128, и использовать вместо приведения uint64 к int64 ( возможно переполнение )
		case T_TYPE_CHAR: return addUInt32WithChar(a, b.value.ch);
		case T_TYPE_STRING: return addUInt32WithString(a, b.value.str);
	}
}

T addInt64WithT(int32 a, T b) {
	switch (b.type) {
		case T_TYPE_INT8: return;
		case T_TYPE_INT16: return;
		case T_TYPE_INT32: return;
		case T_TYPE_INT64: return;
		case T_TYPE_UINT8: return;
		case T_TYPE_UINT16: return;
		case T_TYPE_UINT32: return;
		case T_TYPE_UINT64: return;
		case T_TYPE_CHAR: return;
		case T_TYPE_STRING: return;
	}
}

T addUInt64WithT(int32 a, T b) {
	switch (b.type) {
		case T_TYPE_INT8: return;
		case T_TYPE_INT16: return;
		case T_TYPE_INT32: return;
		case T_TYPE_INT64: return;
		case T_TYPE_UINT8: return;
		case T_TYPE_UINT16: return;
		case T_TYPE_UINT32: return;
		case T_TYPE_UINT64: return;
		case T_TYPE_CHAR: return;
		case T_TYPE_STRING: return;
	}
}

T addCharWithT(Char a, T b) {
	switch (b.type) {
		case T_TYPE_INT8: return;
		case T_TYPE_INT16: return;
		case T_TYPE_INT32: return;
		case T_TYPE_INT64: return;
		case T_TYPE_UINT8: return;
		case T_TYPE_UINT16: return;
		case T_TYPE_UINT32: return;
		case T_TYPE_UINT64: return;
		case T_TYPE_CHAR: return;
		case T_TYPE_STRING: return;
	}
}

T addStringWithT(String a, T b) {
	switch (b.type) {
		case T_TYPE_INT8: return;
		case T_TYPE_INT16: return;
		case T_TYPE_INT32: return;
		case T_TYPE_INT64: return;
		case T_TYPE_UINT8: return;
		case T_TYPE_UINT16: return;
		case T_TYPE_UINT32: return;
		case T_TYPE_UINT64: return;
		case T_TYPE_CHAR: return;
		case T_TYPE_STRING: return;
	}
}

T T_Add(T a, T b) {
	switch (a.type) {
		case T_TYPE_INT8: return addInt32WithT((int32)a.value.numX8, b);
		case T_TYPE_INT16: return addInt32WithT((int32)a.value.numX16, b);
		case T_TYPE_INT32: return addInt32WithT((int32)a.value.numX32, b);
		case T_TYPE_INT64: return addInt64WithT(a.value.numX64, b);
		
		case T_TYPE_UINT8: return addUInt32WithT((uint32)a.value.numUX8, b);
		case T_TYPE_UINT16: return addUInt32WithT((uint32)a.value.numUX16, b);
		case T_TYPE_UINT32: return addUInt32WithT((uint32)a.value.numUX32, b);
		case T_TYPE_UINT64: return addUInt64WithT(a.value.numUX64, b);

		case T_TYPE_CHAR: return addCharWithT(a.value.ch, b);
		case T_TYPE_STRING: return addStringWithT(a.value.str, b);
	}
} // Складывание a и b.

T T_Sub(T a, T b) {
	switch (a.type) {
		case T_TYPE_INT8: return;
		case T_TYPE_INT16: return;
		case T_TYPE_INT32: return;
		case T_TYPE_INT64: return;
		case T_TYPE_UINT8: return;
		case T_TYPE_UINT16: return;
		case T_TYPE_UINT32: return;
		case T_TYPE_UINT64: return;
		case T_TYPE_CHAR: return;
		case T_TYPE_STRING: return;
	}
} // Вычитание a и b.

T T_Mul(T a, T b) {
	switch (a.type) {
		case T_TYPE_INT8: return;
		case T_TYPE_INT16: return;
		case T_TYPE_INT32: return;
		case T_TYPE_INT64: return;
		case T_TYPE_UINT8: return;
		case T_TYPE_UINT16: return;
		case T_TYPE_UINT32: return;
		case T_TYPE_UINT64: return;
		case T_TYPE_CHAR: return;
		case T_TYPE_STRING: return;
	}
} // Умножение a и b.

T T_Div(T a, T b) {
	switch (a.type) {
		case T_TYPE_INT8: return;
		case T_TYPE_INT16: return;
		case T_TYPE_INT32: return;
		case T_TYPE_INT64: return;
		case T_TYPE_UINT8: return;
		case T_TYPE_UINT16: return;
		case T_TYPE_UINT32: return;
		case T_TYPE_UINT64: return;
		case T_TYPE_CHAR: return;
		case T_TYPE_STRING: return;
	}
} // Деление a и b.

T T_Mod(T a, T b) {
	switch (a.type) {
		case T_TYPE_INT8: return;
		case T_TYPE_INT16: return;
		case T_TYPE_INT32: return;
		case T_TYPE_INT64: return;
		case T_TYPE_UINT8: return;
		case T_TYPE_UINT16: return;
		case T_TYPE_UINT32: return;
		case T_TYPE_UINT64: return;
		case T_TYPE_CHAR: return;
		case T_TYPE_STRING: return;
	}
} // Взятие остатка от деления a и b.

double doubleFromDecimal(Decimal decimal) {
	return (double)decimal.numerator / (double)decimal.denominator;
}

Decimal doubleToDecimal(double x) {
	uint8 step = 0;

	double denominator = 1.0f;

	while (getFirstNumberAfterDecimalPoint(x * denominator) != 0 && step < MAX_DOUBLE_STEPS) {
		denominator *= 10.0f;

		step++;
	}

	return (Decimal){.numerator = (int32)(x * denominator), 
					 .denominator = (int32)denominator
					};
}