#ifndef _GLYPH_H
#define _GLYPH_H

#include "core/types.h"

typedef uint16 UGSMGlyphCode;

bool UGSMcheckGlyphCodeIsReserved(UGSMGlyphCode glyphCode);

void UGSMreserveGlyphCode(UGSMGlyphCode glyphCode);

void UGSMfreeGlyphCode(UGSMGlyphCode glyphCode);

UGSMGlyphCode UGSMgetFreeSpaceForGlyph();

UGSMGlyphCode UGSMgenerateGlyphCode();

#endif