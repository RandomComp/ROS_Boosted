#ifndef _RANDOM_OS_UGSM_H
#define _RANDOM_OS_UGSM_H

#include "core/basic_types.h"

#include "charset/ugsm/ugsm_types.h"

uint32 UGSMgetLength(UGSM_Code* str);

UGSM_Code UGSMloadGlyphSet(UGSM_Code glyphSet, size_t length);

UGSM_Code UGSMloadGlyph(UGSMGlyph glyph);

UGSMGlyph* UGSMgetGlyph(UGSM_Code glyphCode);

void UGSMASCIIputString(int8* str);

void UGSMASCIIputChar(int8 c);

UGSM_Code UGSMASCIICharToUGSM(int8 c);

UGSM_Code UGSMdigitToUGSM(uint8 digit);

void UGSMASCIIsetString(uint16 x, uint16 y, int8* str);

void UGSMASCIIsetChar(uint16 x, uint16 y, int8 c);

#endif