#ifndef _R_OS_FONT_TYPES_H
#define _R_OS_FONT_TYPES_H

// Полностью заимствованно из Random OS Boosted

#include "types.h"

typedef word Font_ReserveCode;

typedef struct Glyph {
	size_t width, height;

	byte* data;
} Glyph;

typedef struct Font {
	Glyph* glyphs;

	size_t glyph_offset, glyph_count;
} Font;

#endif