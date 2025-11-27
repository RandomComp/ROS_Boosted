#ifndef _ABC_H
#define _ABC_H

#include "core/types.h"

#include "charset/ugsm.h"

#define ENGLISH_LETTERS_NUMBER 26

bool UGSMGlyphIsControlCharacter(UGSMGlyphCode glyphCode);

bool UGSMGlyphIsLetter(UGSMGlyphCode glyphCode);

bool UGSMGlyphIsDigit(UGSMGlyphCode glyphCode);

bool UGSMGlyphIsLetterOrDigit(UGSMGlyphCode glyphCode);

UGSMGlyphCode UGSMGlyphToUpperCase(UGSMGlyphCode glyphCode);

UGSMGlyphCode UGSMGlyphToLowerCase(UGSMGlyphCode glyphCode);

#endif