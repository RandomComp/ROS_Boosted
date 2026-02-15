#ifndef _RANDOM_OS_UGSM_H
#define _RANDOM_OS_UGSM_H

#include "core/basic_types.h"

#include "charset/ugsm/ugsm_types.h"

UGSM_Code UGSM_ASCIICharToUGSM(uint8 c);

UGSM_Code UGSM_fromDigit(uint8 digit);

bool UGSM_GlyphIsControlCharacter(UGSM_Code glyphCode);

bool UGSM_GlyphIsLetter(UGSM_Code glyphCode);

bool UGSM_GlyphIsDigit(UGSM_Code glyphCode);

bool UGSM_GlyphIsLetterOrDigit(UGSM_Code glyphCode);

UGSM_Code UGSM_GlyphToUpperCase(UGSM_Code glyphCode);

UGSM_Code UGSM_GlyphToLowerCase(UGSM_Code glyphCode);

#endif