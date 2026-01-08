#ifndef _RANDOM_OS_CHAR_H
#define _RANDOM_OS_CHAR_H

#include "core/types/basic_types.h"

#include "charset/ugsm.h"

#include "charset/cp437.h"

#include "core/string.h"

static inline Char charCharsetToASCII(Char ch) {
	CP437_CharacterCode result = CP437_CHAR_NULL;

	if (ch.charset == CHARSET_ASCII)
		result = ch.ch.ASCIIChar;

	else if (ch.charset == CHARSET_UGSM)
		result = ASCIIUGSMCharToASCII(ch.ch.UGSMChar);

	return newCharFromASCII(result);
}

static inline Char charCharsetToUGSM(Char ch) {
	UGSM_CharacterCode result = UGSM_CHAR_NULL;

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