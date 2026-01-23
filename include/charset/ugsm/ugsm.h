#ifndef _RANDOM_OS_UGSM_H
#define _RANDOM_OS_UGSM_H

#include "core/basic_types.h"

#include "charset/ugsm/ugsm_types.h"

uint32 UGSM_getLength(UGSM_Code* str);

UGSM_Code UGSM_loadGlyphSet(UGSM_Code glyphSet, size_t length);

UGSM_Code UGSM_loadGlyph(UGSM_Glyph glyph);

UGSMGlyph* UGSM_getGlyph(UGSM_Code glyphCode);

UGSM_Code UGSM_ASCIICharToUGSM(c_char c);

UGSM_Code UGSM_digitToUGSM(uint8 digit);

bool UGSM_GlyphIsControlCharacter(UGSM_Code glyphCode);

bool UGSM_GlyphIsLetter(UGSM_Code glyphCode);

bool UGSM_GlyphIsDigit(UGSM_Code glyphCode);

bool UGSM_GlyphIsLetterOrDigit(UGSM_Code glyphCode);

UGSM_Code UGSM_GlyphToUpperCase(UGSM_Code glyphCode);

UGSM_Code UGSM_GlyphToLowerCase(UGSM_Code glyphCode);

#endif