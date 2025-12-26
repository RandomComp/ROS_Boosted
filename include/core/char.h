#ifndef _RANDOM_OS_CHAR_H
#define _RANDOM_OS_CHAR_H

#include "core/types.h"

#include "charset/ugsm.h"

#include "charset/cp437.h"

#include "core/string.h"

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

inline Char newChar(Charset charset, CharUnion ch) {
	return (Char){.charset = charset, .ch = ch};
}

inline Char* getCharArrayFromString(String str) {
	return (Char*)(str.region->memory);
}

inline CharUnion charUnionFromUGSMChar(UGSMGlyphCode code) {
	return (CharUnion){.UGSMChar = code};
}

inline CharUnion charUnionFromASCIIChar(int8 code) {
	return (CharUnion){.ASCIIChar = code};
}

inline Char charCharsetToASCII(Char ch) {
	CP437_CharacterCode result = CP437_CHAR_NULL;

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

#endif