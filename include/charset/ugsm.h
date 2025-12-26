#ifndef _RANDOM_OS_UGSM_H
#define _RANDOM_OS_UGSM_H

#include "core/types.h"

#include "charset/glyph.h"

#include "charset/ugsm_types.h"

uint32 UGSMgetLength(UGSMGlyphCode* str);

UGSMGlyphSetCode UGSMloadGlyphSet(UGSMGlyphSet glyphSet, UGSMGlyphSetSize length);

UGSMGlyphCode UGSMloadGlyph(UGSMGlyph glyph);

UGSMGlyph* UGSMgetGlyph(UGSMGlyphCode glyphCode);

void UGSMASCIIputString(int8* str);

void UGSMASCIIputChar(int8 c);

UGSMGlyphCode UGSMASCIICharToUGSM(int8 c);

UGSMGlyphCode UGSMdigitToUGSM(uint8 digit);

void UGSMASCIIsetString(uint16 x, uint16 y, int8* str);

void UGSMASCIIsetChar(uint16 x, uint16 y, int8 c);

#endif