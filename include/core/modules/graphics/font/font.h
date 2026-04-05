#ifndef _R_OS_FONT_H
#define _R_OS_FONT_H

#include "core/basic_types.h"

#include "graphics/font/font_types.h"

Glyph* Font_copy_glyph(Glyph* dest, const Glyph* src);

ErrorCode Font_copy(Font** dest_ptr, const Font* src);

Font_ReserveCode Font_load(Font* font);

#endif