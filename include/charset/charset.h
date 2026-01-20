#ifndef _RANDOM_OS_CHARSET_H
#define _RANDOM_OS_CHARSET_H

#include "core/basic_types.h"

#include "charset/ugsm/ugsm_types.h"

#include "charset/cp437/cp437_types.h"

typedef enum Charset {
	CHARSET_UGSM,
	CHARSET_ASCII,
} Charset;

typedef union CharUnion {
	UGSM_Code	UGSMChar;
	
	CP437_Code	ASCIIChar;
} CharUnion;

typedef struct CharacterCode {
	Charset charset;

	CharUnion ch;
} CharacterCode;

bool Charset_UGSMGlyphIsControlCharacter(UGSM_Code glyphCode);

bool Charset_UGSMGlyphIsLetter(UGSM_Code glyphCode);

bool Charset_UGSMGlyphIsDigit(UGSM_Code glyphCode);

bool Charset_UGSMGlyphIsLetterOrDigit(UGSM_Code glyphCode);

UGSM_Code Charset_UGSMGlyphToUpperCase(UGSM_Code glyphCode);

UGSM_Code Charset_UGSMGlyphToLowerCase(UGSM_Code glyphCode);

#endif