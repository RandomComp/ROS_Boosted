#ifndef _STD_H
#define _STD_H

#include "core/types.h"

#include "charset/glyph.h"

#include "charset/ugsm.h"

#define width 800

#define height 600

void STDInit(void);

uint32 getStringLength(UGSMGlyphCode str[6]);

void setConsoleCursorPosition(int16 _x, int16 _y);

void setConsoleCursorVisible(bool bVisible);

void setString(uint16 x, uint16 y, UGSMGlyphCode str[6]);

void putString(UGSMGlyphCode str[384]);

void setChar(uint16 x, uint16 y, UGSMGlyphCode glyphCode);

void putChar(UGSMGlyphCode glyphCode);

void clear(uint32 backgroundColor);

void swap(void);

#endif