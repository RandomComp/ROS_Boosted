#include "graphics/font/font.h"

#include "core/basic_types.h"

#include "std/std.h"

#include "math/math.h"

#include "format/bcd.h"

#include "exceptions/warnings/warning_types.h"

#include "exceptions/errors/error_types.h"

#include "drivers/memory/ram.h"

#include "builtins/mem.h"

static byte* reserveTable = nullptr;

static Font* fonts = nullptr;

static size_t glyphCount, fontCount = 0;

static bool bInitialized = false;

static Glyph* copyGlyph(Glyph* dest, Glyph* src) {
	if (src == nullptr) {
		throw(
			Exception_errorInvalidArgument(
				"Cannot copy from src to dest, when src = nullptr."
			)
		);

		return nullptr;
	}

	if (dest == nullptr)
		dest = malloc(sizeof(Font), MEMORY_STATUS_ACTIVE);

	dest->width = src->width;

	dest->height = src->height;

	dest->size = src->size;

	dest->data = realloc(dest->data, dest->size);

	memcpy(dest->data, src->data, dest->size);

	return dest;
}

static Font* copyFont(Font* dest, Font* src) {
	if (src == nullptr) {
		throw(
			Exception_errorInvalidArgument(
				"Cannot copy from src to dest, when src = nullptr."
			)
		);

		return nullptr;
	}

	if (dest == nullptr)
		dest = malloc(sizeof(Font), MEMORY_STATUS_ACTIVE);

	if (src->glyphCount == 0) {
		throw(
			Exception_warningInvalidArgument(
				"Nothing to copy ( src->glyphCount = 0 )."
			)
		);

		return nullptr;
	}

	dest->glyphCount = src->glyphCount;

	dest->glyphs = realloc(dest->glyphs, dest->glyphCount * sizeof(Glyph));

	for (size_t i = 0; i < dest->glyphCount; i++) {
		copyGlyph(&dest->glyphs[i], &src->glyphs[i]);
	}

	return dest;
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

Font_ReserveCode Font_load(Font font) {
	Font_ReserveCode fontCode = getFreeSpaceForGlyph();

	size_t fontEnd = glyphCount + font.glyphCount;

	reserveTable = realloc(reserveTable, fontEnd);

	fonts = realloc(fonts, fontEnd);

	for (Font_ReserveCode i = 0; i < font.glyphCount; i++) {
		copyFont(&fonts[i + fontCode], &font.glyphs[i]);
	}

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