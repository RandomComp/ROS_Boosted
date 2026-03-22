#include "graphics/font/font.h"

#include "core/basic_types.h"

#include "std/std.h"

#include "math/math.h"

#include "format/bcd.h"

#include "drivers/memory/ram.h"

#include "builtins/mem.h"

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
		throw(
			Exception_errorInvalidArgument(
				"Unable font copy: src is nullptr."
			)
		);

		return CODE_FAIL;
	}

	if (dest_ptr == nullptr) {
		throw(
			Exception_errorInvalidArgument(
				"Font copy failed: dest_ptr is nullptr."
			)
		);

		return CODE_FAIL;
	}

	if (*dest_ptr == nullptr)
		*dest_ptr = malloc(sizeof(Font));

	Font* dest = *dest_ptr;

	dest->glyph_count = src->glyph_count;

	if (src->glyph_count == 0) {
		throw(
			Exception_warningInvalidArgument(
				"Font copy failed: nothing to copy (src->glyphCount is 0)."
			)
		);

		return CODE_FAIL;
	}

	Glyph* new_glyphs = realloc(dest->glyphs, src->glyph_count * sizeof(Glyph));

	if (new_glyphs == nullptr) {
		throw(
			Exception_fromError(
				ERROR_MEMORY_LACK,
				"Font copy failed "
			)
		);

		return CODE_FAIL;
	}

	dest->glyphs = realloc(dest->glyphs, src->glyph_count * sizeof(Glyph));

	for (size_t i = 0; i < dest->glyph_count; i++) {
		Font_copy_glyph(&dest->glyphs[i], &src->glyphs[i]);
	}

	return CODE_OK;
}

static bool isCodeReserved(Font_ReserveCode code) {
	// TODO: Обработать случаи когда code >= glyphCount

	return checkBit(reserveTable[getByteIndex(code)], getBitIndex(code));
}

static void reserveCode(Font_ReserveCode code) {
	if (isCodeReserved(code)) // check for reserved
		ERROR_throw(ERROR_GLYPH_CODE_RESERVED); // if the glyph is reserved, then we issue the corresponding error

	else enableBit(&reserveTable[getByteIndex(code)], getBitIndex(code));
}

static void freeGlyphCode(Font_ReserveCode code) {
	if (isCodeReserved(code)) // check for reserved
		disableBit(&reserveTable[getByteIndex(code)], getBitIndex(code));

	else ERROR_throw(ERROR_GLYPH_CODE_NOT_RESERVED); // if the glyph is not reserved, then we issue the corresponding error
}

static Font_ReserveCode getFreeSpaceForGlyph() {
	for (Font_ReserveCode i = 0; i < glyphCount; i++) {
		
	}

	return 0;
}

Font_ReserveCode Font_load(Font* font) {
	Font_ReserveCode fontCode = getFreeSpaceForGlyph();

	size_t fontEnd = glyphCount + font->glyph_count;

	reserveTable = realloc(reserveTable, fontEnd);

	fonts = realloc(fonts, fontEnd);

	Font_copy(&fonts[fontCode], font);

	return fontCode;
}

Glyph* Font_getGlyph(Font_ReserveCode code) {
	if (!isCodeReserved(code)) {
		klog(LOG_WARNING, "Font get glyph warning: code not reserved");
	}

	return ;
}

Font_ReserveCode generateGlyphCode() {
	Font_ReserveCode glyphCode = getFreeSpaceForGlyph();

	reserveGlyphCode(glyphCode);

	return glyphCode;
}