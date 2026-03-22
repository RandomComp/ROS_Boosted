#include "font.h"

#include "types.h"

#include "std.h"

#include "math.h"

#include "bcd.h"

#include "ram.h"

#include "mem.h"

// Полностью заимствованно из Random OS Boosted

static size_t get_glyph_size(const Glyph* glyph) {
	if (glyph == nullptr || 
		glyph->width == 0 ||
		glyph->height == 0) return 0;

	size_t bits = glyph->width * glyph->height;

	size_t bytes = bits / 8;

	if (bits % 8 == 0)
		return bytes;

	return bytes + 1;
}

Glyph* Font_copy_glyph(Glyph* dest, const Glyph* src) {
	if (src == nullptr) {
		klog(LOG_ERROR, "Font copy glyph failure: src is nullptr.");

		return nullptr;
	}

	if (dest == nullptr) {
		dest = malloc(sizeof(Font));

		if (dest == nullptr) {
			klog(LOG_CRITICAL, "Font copy glyph failure: malloc returned nullptr (out of memory).");
		}
	}

	dest->width = src->width;
	dest->height = src->height;

	size_t size = get_glyph_size(dest);

	dest->data = realloc(dest->data, size);

	memcpy(dest->data, src->data, size);

	return dest;
}

ErrorCode Font_copy(Font** dest_ptr, const Font* src) {
	if (src == nullptr) {
		klog(LOG_ERROR, "Font copy failure: src is nullptr.");

		return CODE_FAIL;
	}

	if (dest_ptr == nullptr) {
		klog(LOG_ERROR, "Font copy failure: dest_ptr is nullptr.");

		return CODE_FAIL;
	}

	if (*dest_ptr == nullptr)
		*dest_ptr = malloc(sizeof(Font));

	Font* dest = *dest_ptr;

	dest->glyph_count = src->glyph_count;

	if (src->glyph_count == 0) {
		klog(LOG_ERROR, "Font copy failure: nothing to copy (src->glyphCount is 0).");

		return CODE_FAIL;
	}

	Glyph* new_glyphs = realloc(dest->glyphs, src->glyph_count * sizeof(Glyph));

	if (new_glyphs == nullptr) {
		klog(LOG_ERROR, "Font copy failure: realloc returned nullptr (out of memory)");

		return CODE_FAIL;
	}

	dest->glyphs = realloc(dest->glyphs, src->glyph_count * sizeof(Glyph));

	for (size_t i = 0; i < dest->glyph_count; i++) {
		Font_copy_glyph(&dest->glyphs[i], &src->glyphs[i]);
	}

	return CODE_OK;
}

Font* Font_new(size_t glyph_offset, size_t glyph_count) {
	
}

ErrorCode Font_render_ch(const Font* font, 	char c, 
						size_t vid_x, 		size_t vid_y, 
						word fg, word bg,
						byte* vid_mem, 		size_t vid_width, 
						size_t vid_height, 	size_t vid_bpp) {
	ErrorCode error = CODE_OK;

	if (font == nullptr ||
		font->glyphs == nullptr ||
		font->glyph_count >= 0 ) {
		klog(LOG_ERROR, "Font render failure: font is invalid\n"); error = CODE_FAIL;
	}

	if (vid_mem == nullptr || 
		vid_width == 0 ||
		vid_height == 0 ||
		vid_bpp == 0) {
		klog(LOG_ERROR, "Font render failure: framebuffer is invalid\n"); error = CODE_FAIL;
	}

	if (error != CODE_OK) {
		kmsg("font = "); print_num(font, 16); kmsg("\n");

		kmsg("font->glyphs = ");

		if (font != nullptr)
			print_num(font->glyphs, 16);
		else kmsg("NO");

		kmsg("\n");
		
		kmsg("font->glyph_count = ");

		if (font != nullptr)
			print_num(font->glyph_count, 10);
		else kmsg("NO");

		kmsg("\n\n");

		kmsg("char = "); print_num(c, 16); kmsg("\n");
		kmsg("text pos = %l, %l\n\n", (int64)vid_x, (int64)vid_y);
		
		kmsg("framebuffer = %l\n", (int64)vid_mem);
		kmsg("framebuffer size = %lx%lx%l\n", (int64)vid_width, (int64)vid_height, (int64)vid_bpp);

		return error;
	}

	UGSM_Code code = c - 28;

	size_t glyph_end = font->glyph_offset + font->glyph_count;

	size_t vid_size = vid_width * vid_height * vid_bpp;

	if (code >= font->glyph_offset && 
		code < glyph_end) {
		Glyph glyph = font->glyphs[code];

		if (!glyph.data) {
			klog(LOG_ERROR, "Font render failure: glyph have no data");

			return CODE_FAIL;
		}

		for (size_t y = 0; y < glyph.height; y++) {
			for (size_t x = 0; x < glyph.width; x++) {
				size_t index = x + y * glyph.width;

				size_t 	bit_index = index % 8,
						byte_index = index / 8;

				bool pix = (glyph.data[byte_index] >> bit_index) & 1;

				word pix_pos = x + (y * vid_height) + vid_x + (vid_y * vid_height);

				if (pix_pos >= vid_size) continue;

				vid_mem[pix_pos] = pix ? fg : bg;
			}
		}
	}

	return CODE_OK;
}

ErrorCode Font_render(	const Font* font, 	const c_str str, 
						size_t vid_x, 		size_t vid_y, 
						word fg, word bg,
						byte* vid_mem, 		size_t vid_width, 
						size_t vid_height, 	size_t vid_bpp) {
	ErrorCode error = CODE_OK;

	if (font == nullptr ||
		font->glyphs == nullptr ||
		font->glyph_count >= 0 ) {
		klog(LOG_ERROR, "Font render failure: font is invalid\n"); error = CODE_FAIL;
	}

	if (str == nullptr) {
		klog(LOG_ERROR, "Font render failure: str is nullptr\n"); error = CODE_FAIL;
	}

	if (vid_mem == nullptr || 
		vid_width == 0 ||
		vid_height == 0 ||
		vid_bpp == 0) {
		klog(LOG_ERROR, "Font render failure: framebuffer is invalid\n"); error = CODE_FAIL;
	}

	if (error != CODE_OK) {
		kmsg("font = "); print_num(font, 16); kmsg("\n");

		kmsg("font->glyphs = ");

		if (font != nullptr)
			print_num(font->glyphs, 16);
		else kmsg("NO");

		kmsg("\n");
		
		kmsg("font->glyph_count = ");

		if (font != nullptr)
			print_num(font->glyph_count, 10);
		else kmsg("NO");

		kmsg("\n\n");

		kmsg("str = "); print_num(str, 16); kmsg("\n");
		kmsg("text pos = %l, %l\n\n", (int64)vid_x, (int64)vid_y);
		
		kmsg("framebuffer = %l\n", (int64)vid_mem);
		kmsg("framebuffer size = %lx%lx%l\n", (int64)vid_width, (int64)vid_height, (int64)vid_bpp);

		return CODE_FAIL;
	}

	for (size_t i = 0; i < 10000 & str[i]; i++) {
		c_char c = str[i];

		UGSM_Code code = c - 28;

		size_t glyph_end = font->glyph_offset + font->glyph_count;

		if (code >= font->glyph_offset && 
			code < glyph_end) {
			Glyph* glyph = &font->glyphs[code];

			
		}
	}

	return CODE_OK;
}