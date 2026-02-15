#include "graphics/font/font.h"

#include "core/basic_types.h"

#include "std/std.h"

#include "math/math.h"

#include "format/bcd.h"

#include "exceptions/warnings/warning_types.h"

#include "exceptions/errors/error.h"

#include "drivers/memory/ram.h"

#include "builtins/mem.h"

static byte* reserveTable = nullptr;

static Font* fonts = nullptr;

static size_t glyphCount, fontCount = 0;

static bool bInitialized = false;

static Glyph* copyGlyph(Glyph* dest, const Glyph* src) {
	if (src == nullptr) {
		throw(
			Exception_errorInvalidArgument(
				"Unable copy from src to dest, when src is nullptr."
			)
		);

		return nullptr;
	}

	if (dest == nullptr)
		dest = malloc(sizeof(Font));

	dest->width = src->width;

	dest->height = src->height;

	dest->size = src->size;

	dest->data = realloc(dest->data, dest->size);

	memcpy(dest->data, src->data, dest->size);

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

	dest->glyphCount = src->glyphCount;

	if (src->glyphCount == 0) {
		throw(
			Exception_warningInvalidArgument(
				"Font copy failed: nothing to copy (src->glyphCount is 0)."
			)
		);

		return CODE_FAIL;
	}

	Glyph* new_glyphs = realloc(dest->glyphs, src->glyphCount * sizeof(Glyph));

	if (new_glyphs == nullptr) {
		throw(
			Exception_fromError(
				ERROR_MEMORY_LACK,
				"Font copy failed "
			)
		);

		return CODE_FAIL;
	}

	dest->glyphs = realloc(dest->glyphs, src->glyphCount * sizeof(Glyph));

	for (size_t i = 0; i < dest->glyphCount; i++) {
		copyGlyph(&dest->glyphs[i], &src->glyphs[i]);
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

	size_t fontEnd = glyphCount + font->glyphCount;

	reserveTable = realloc(reserveTable, fontEnd);

	fonts = realloc(fonts, fontEnd);

	Font_copy(&fonts[fontCode], font);

	return fontCode;
}

UGSM_Code Font_loadGlyph(UGSMGlyph glyph) {
	UGSM_Code result = generateGlyphCode();

	memcpy(UGSM[result], glyph, UGSMGlyphHeight);

	Font_size++;

	return result;
}

UGSMGlyph* Font_getGlyph(UGSM_Code glyphCode) {
	if (!checkGlyphCodeIsReserved(glyphCode))
		ERROR_throw(UGSM_GLYPH_NOT_RESERVED_BUT_WE_TRY_USE);
	
	assert

	return &UGSM[glyphCode];
}

Font_ReserveCode generateGlyphCode() {
	Font_ReserveCode glyphCode = getFreeSpaceForGlyph();

	reserveGlyphCode(glyphCode);

	return glyphCode;
}