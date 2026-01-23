#ifndef _RANDOM_OS_FONT_TYPES_H
#define _RANDOM_OS_FONT_TYPES_H

#include "core/basic_types.h"

#define FONTS_MAX_COUNT 8

#define FONT_CHAR_WIDTH 8

#define FONT_CHAR_HEIGHT 16

typedef dword Font_ReserveCode;

typedef struct Glyph {
	size_t width, height;

	size_t size;

	byte* data;

	Font_ReserveCode code;

	bool isReserved;
} Glyph;

typedef struct Font {
	Glyph* glyphs;

	size_t glyphCount;
} Font;

#endif