#include "std/string/string.h"

#include "core/modules/std/string/char.h"

#include "core/basic_types.h"

#include "core/modules/exceptions/exception.h"

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
		case T_TYPE_SINT:   return intToString(x.value.signedNum);
		
		case T_TYPE_UINT:  return uintToString(x.value.unsignedNum);

		case T_TYPE_CHAR:   return charToString(x.value.ch);
		
		case T_TYPE_STRING: return x.value.str;
	}

	warn(UNKNOWN_T_TYPE_WARNING);

	String defaultResult = newString(1);

	setCharToString(&defaultResult, 0, newCharFromUGSM(UGSM_CHAR_NULL));

	return defaultResult;
}