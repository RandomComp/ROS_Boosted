#ifndef _RANDOM_OS_CHAR_H
#define _RANDOM_OS_CHAR_H

#include "core/basic_types.h"

#include "std/string/char_types.h"

#include "charset/ugsm/ugsm.h"

#include "charset/cp437/cp437.h"

#include "std/string/string_types.h"

static inline CharUnion newCharUnionFromASCII(int8 ch) {
	return (CharUnion){.ASCIIChar = ch};
}

static inline CharUnion newCharUnionFromUGSM(UGSM_Code ch) {
	return (CharUnion){.UGSMChar = ch};
}

static inline Char newCharFromASCII(int8 ch) {
	return (Char){.charset = CHARSET_ASCII, .ch = newCharUnionFromASCII(ch)};
}

static inline Char newCharFromUGSM(UGSM_Code ch) {
	return (Char){.charset = CHARSET_UGSM, .ch = newCharUnionFromUGSM(ch)};
}

static inline Char newChar(Charset charset, CharUnion ch) {
	return (Char){.charset = charset, .ch = ch};
}

static inline Char* getCharArrayFromString(String* str) {
	return (Char*)(str->region->memory);
}

static inline CharUnion charUnionFromUGSMChar(UGSM_Code code) {
	return (CharUnion){.UGSMChar = code};
}

static inline CharUnion charUnionFromASCIIChar(int8 code) {
	return (CharUnion){.ASCIIChar = code};
}

static inline Char charCharsetToASCII(Char ch) {
	CP437_Code result = CP437_CHAR_NULL;

	if (ch.charset == CHARSET_ASCII)
		result = ch.ch.ASCIIChar;

	else if (ch.charset == CHARSET_UGSM)
		result = CP437_fromUGSMChar(ch.ch.UGSMChar);

	return newCharFromASCII(result);
}

static inline Char charCharsetToUGSM(Char ch) {
	UGSM_Code result = UGSM_CHAR_NULL;

	if (ch.charset == CHARSET_ASCII)
		result = UGSMASCIICharToUGSM(ch.ch.ASCIIChar);

	else if (ch.charset == CHARSET_UGSM)
		result = ch.ch.UGSMChar;

	return newCharFromUGSM(result);
}

static inline Char digitToChar(uint8 digit) {
	return newCharFromUGSM(UGSMdigitToUGSM(digit));
}

#endif