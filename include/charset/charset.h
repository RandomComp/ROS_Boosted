#ifndef _RANDOM_OS_CHARSET_H
#define _RANDOM_OS_CHARSET_H

#include "core/types/basic_types.h"

#include "charset/types/ugsm_types.h"

#include "charset/types/ascii_types.h"

typedef enum Charset {
	CHARSET_UGSM,
	CHARSET_ASCII,
} Charset;

typedef union CharUnion {
	UGSM_CharacterCode	UGSMChar;
	
	ASCII_CharacterCode	ASCIIChar;
} CharUnion;

typedef struct CharacterCode {
	Charset charset;

	CharUnion ch;
} CharacterCode;

bool Charset_UGSMGlyphIsControlCharacter(UGSM_CharacterCode glyphCode);

bool Charset_UGSMGlyphIsLetter(UGSM_CharacterCode glyphCode);

bool Charset_UGSMGlyphIsDigit(UGSM_CharacterCode glyphCode);

bool Charset_UGSMGlyphIsLetterOrDigit(UGSM_CharacterCode glyphCode);

UGSM_CharacterCode Charset_UGSMGlyphToUpperCase(UGSM_CharacterCode glyphCode);

UGSM_CharacterCode Charset_UGSMGlyphToLowerCase(UGSM_CharacterCode glyphCode);

#endif