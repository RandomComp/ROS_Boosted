#include "core/T.h"

#include "core/types.h"

T addInt32WithChar(int32 a, Char b) {
	CharUnion result = b.ch;

	if (b.charset == CHARSET_ASCII)
		result.ASCIIChar = (result.ASCIIChar + a) % UINT8_MAX;

	else if (b.charset == CHARSET_UGSM)
		result.UGSMChar = (result.UGSMChar + a) % UINT16_MAX;
	
	return charToT(newChar(b.charset, result));
}

T addInt32WithString(int32 a, String b) {
	return stringToT(stringConcatenate(int32ToString(a), b));
}

T addUInt32WithChar(uint32 a, Char b) {
	CharUnion result = b.ch;

	if (b.charset == CHARSET_ASCII)
		result.ASCIIChar = (result.ASCIIChar + a) % UINT8_MAX;

	else if (b.charset == CHARSET_UGSM)
		result.UGSMChar = (result.UGSMChar + a) % UINT16_MAX;
	
	return charToT(newChar(b.charset, result));
}

T addUInt32WithString(uint32 a, String b) {
	return stringToT(stringConcatenate(uint32ToString(a), b));
}

T addInt64WithChar(int64 a, Char b) {
	CharUnion result = b.ch;

	if (b.charset == CHARSET_ASCII)
		result.ASCIIChar = (result.ASCIIChar + a) % UINT8_MAX;

	else if (b.charset == CHARSET_UGSM)
		result.UGSMChar = (result.UGSMChar + a) % UINT16_MAX;
	
	return charToT(newChar(b.charset, result));
}

T addInt64WithString(int64 a, String b) {
	return stringToT(stringConcatenate(int64ToString(a), b));
}

T addUInt64WithChar(uint64 a, Char b) {

}

T addUInt64WithString(uint64 a, String b) {
	
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

T addUInt32WithT(uint32 a, T b) {
	switch (b.type) {
		case T_TYPE_INT8: return int64ToT((int64)a + (int64)b.value.numX8);
		case T_TYPE_INT16: return int64ToT((int64)a + (int64)b.value.numX16);
		case T_TYPE_INT32: return int64ToT((int64)a + (int64)b.value.numX32);
		case T_TYPE_INT64: return int64ToT((int64)a + (int64)b.value.numX64);
		case T_TYPE_UINT8: return uint32ToT(a + (uint32)b.value.numUX8);
		case T_TYPE_UINT16: return uint32ToT((uint64)a + (uint64)b.value.numUX16);
		case T_TYPE_UINT32: return uint64ToT((uint64)a + (uint64)b.value.numUX32);
		case T_TYPE_UINT64: return uint32ToT((uint64)a + (uint64)b.value.numUX64); // TODO: Добавить uint128/int128, и использовать вместо приведения uint64 к int64 ( возможно переполнение )
		case T_TYPE_CHAR: return addUInt32WithChar(a, b.value.ch);
		case T_TYPE_STRING: return addUInt32WithString(a, b.value.str);
	}
}

T addInt64WithT(int64 a, T b) {
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

T addUInt64WithT(uint64 a, T b) {
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