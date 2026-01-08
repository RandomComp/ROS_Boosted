#ifndef _RANDOM_OS_CHAR_TYPES_H
#define _RANDOM_OS_CHAR_TYPES_H

#include "charset/charset.h"

typedef struct Char {
	Charset charset;

	CharUnion ch;
} Char;

static inline CharUnion newCharUnionFromASCII(int8 ch) {
	return (CharUnion){.ASCIIChar = ch};
}

static inline CharUnion newCharUnionFromUGSM(UGSM_CharacterCode ch) {
	return (CharUnion){.UGSMChar = ch};
}

static inline Char newCharFromASCII(int8 ch) {
	return (Char){.charset = CHARSET_ASCII, .ch = newCharUnionFromASCII(ch)};
}

static inline Char newCharFromUGSM(UGSM_CharacterCode ch) {
	return (Char){.charset = CHARSET_UGSM, .ch = newCharUnionFromUGSM(ch)};
}

static inline Char newChar(Charset charset, CharUnion ch) {
	return (Char){.charset = charset, .ch = ch};
}

static inline Char* getCharArrayFromString(String str) {
	return (Char*)(str.region->memory);
}

static inline CharUnion charUnionFromUGSMChar(UGSM_CharacterCode code) {
	return (CharUnion){.UGSMChar = code};
}

static inline CharUnion charUnionFromASCIIChar(int8 code) {
	return (CharUnion){.ASCIIChar = code};
}

#endif