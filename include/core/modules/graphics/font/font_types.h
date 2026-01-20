#ifndef _RANDOM_OS_FONT_TYPES_H
#define _RANDOM_OS_FONT_TYPES_H

#include "core/basic_types.h"

#define FONT_MAX_CHAR_LOADABLE_COUNT 256

#define FONTS_MAX_COUNT 8

#define FONT_CHAR_WIDTH 8

#define FONT_CHAR_HEIGHT 16

typedef byte Font_Char[FONT_CHAR_HEIGHT];

typedef byte Font[FONT_MAX_CHAR_LOADABLE_COUNT][FONT_CHAR_HEIGHT];

typedef dword Font_ReserveCode;

typedef struct Font_CharacterInfo {
    uint8 widthSize, heightSize;

    Font_ReserveCode fontCode;
} Font_CharacterInfo;

#endif