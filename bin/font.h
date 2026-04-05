#ifndef _R_OS_FONT_H
#define _R_OS_FONT_H

// Полностью заимствованно из Random OS Boosted

#include "types.h"

#include "font_types.h"

Glyph* Font_copy_glyph(Glyph* dest, const Glyph* src);

ErrorCode Font_copy(Font** dest_ptr, const Font* src);

Font* Font_new(size_t glyph_offset, size_t glyph_count);

ErrorCode Font_render_ch(const Font* font, 	char c, 
						size_t vid_x, 		size_t vid_y, 
						word fg, word bg,
						byte* vid_mem, 		size_t vid_width, 
						size_t vid_height, 	size_t vid_bpp);

ErrorCode Font_render(const Font* font, const c_str str, 
						size_t vid_x, size_t vid_y,
						word fg, word bg,
						byte* vid_mem, size_t vid_width, 
						size_t vid_height, size_t vid_bpp);

#endif