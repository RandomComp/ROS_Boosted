#ifndef _R_OS_FONT_TYPES_H
#define _R_OS_FONT_TYPES_H

#include "core/basic_types.h"

#define FONTS_MAX_COUNT 8

#define FONT_CHAR_WIDTH 8

#define FONT_CHAR_HEIGHT 16

typedef word Font_ReserveCode;

typedef struct Glyph {
	size_t width, height;

	byte* data;

	Font_ReserveCode code;

	bool is_reserved;
} Glyph;

typedef struct Font {
	Glyph* glyphs;

	size_t glyph_count;
} Font;

#endif