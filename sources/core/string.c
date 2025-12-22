#include "core/string.h"

#include "core/char.h"

#include "core/types.h"

#include "core/warning.h"

String int64ToString(int64 x) {
	String result = newString(getNumberOfDigits64(x));

	setCharToString(&result, 0, newCharFromUGSM(UGSM_CHAR_0));

	uint32 index = 0;

	while (x != 0) {
		Char ch = digitToChar(getFirstNumber64(x));

		setCharToString(&result, result.length - index, ch);

		x /= 10;

		index++;
	}

	return result;
}

String uint64ToString(uint64 x) {
	String result = newString(getNumberOfDigitsU64(x));

	setCharToString(&result, 0, newCharFromUGSM(UGSM_CHAR_0));

	uint32 index = 0;

	while (x != 0) {
		Char ch = digitToChar(getFirstNumberU64(x));

		setCharToString(&result, result.length - index, ch);

		x /= 10;

		index++;
	}

	return result;
}

String int32ToString(int32 x) {
	String result = newString(getNumberOfDigits32(x));

	setCharToString(&result, 0, newCharFromUGSM(UGSM_CHAR_0));

	uint32 index = 0;

	while (x != 0) {
		Char ch = digitToChar(getFirstNumber32(x));

		setCharToString(&result, result.length - index, ch);

		x /= 10;

		index++;
	}

	return result;
}

String uint32ToString(uint32 x) {
	String result = newString(getNumberOfDigitsU32(x));

	setCharToString(&result, 0, newCharFromUGSM(UGSM_CHAR_0));

	uint32 index = 0;

	while (x != 0) {
		Char ch = digitToChar(getFirstNumberU32(x));

		setCharToString(&result, result.length - index, ch);

		x /= 10;

		index++;
	}

	return result;
}

String stringConcatenate(String a, String b) {
	if (a.region->memory == 0 || b.region->memory == 0); // TODO: Handle error

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

	warn(UNKNOWN_T_TYPE_WARNING);

	String defaultResult = newString(1);

	setCharToString(&defaultResult, 0, newCharFromUGSM(UGSM_CHAR_NULL));

	return defaultResult;
}