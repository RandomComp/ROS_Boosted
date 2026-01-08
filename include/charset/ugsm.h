#ifndef _RANDOM_OS_UGSM_H
#define _RANDOM_OS_UGSM_H

#include "core/types/basic_types.h"

#include "charset/font.h"

#include "charset/types/ugsm_types.h"

uint32 UGSMgetLength(UGSM_CharacterCode* str);

UGSMGlyphSetCode UGSMloadGlyphSet(UGSMGlyphSet glyphSet, UGSMGlyphSetSize length);

UGSM_CharacterCode UGSMloadGlyph(UGSMGlyph glyph);

UGSMGlyph* UGSMgetGlyph(UGSM_CharacterCode glyphCode);

void UGSMASCIIputString(int8* str);

void UGSMASCIIputChar(int8 c);

UGSM_CharacterCode UGSMASCIICharToUGSM(int8 c);

UGSM_CharacterCode UGSMdigitToUGSM(uint8 digit);

void UGSMASCIIsetString(uint16 x, uint16 y, int8* str);

void UGSMASCIIsetChar(uint16 x, uint16 y, int8 c);

#endif