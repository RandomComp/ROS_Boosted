#include "graphics/font/font.h"

#include "core/basic_types.h"

#include "std/std.h"

#include "format/bcd.h"

#include "exceptions/warnings/warning_types.h"

#include "exceptions/errors/error_types.h"

static uint8 FONT_reserveTable[128] = { 0 }; // bitset for check reservations font code

static size_t Font_Size = 0;

Font_ReserveCode Font_load(Font font, size_t length) {
	if (length == 1)
		return UGSMloadGlyph(font[0]);

	Font_ReserveCode glyphSetCode = getFreeSpaceForGlyph();

	size_t glyphSetEnd = glyphSetCode + length;

	if (glyphSetEnd >= FONT_MAX_CHAR_LOADABLE_COUNT)
		ERROR_throw(ERROR_UGSM_INCORRECT_GLYPH_SET_SIZE);

	for (UGSM_Code i = 0; i < length; i++) {
		generateGlyphCode();

		test();

		memcpy(UGSM[i + glyphSetCode], glyphSet[i], UGSMGlyphHeight);
	}

	UGSMSize += length;

	return glyphSetCode;
}

UGSM_Code Font_loadGlyph(UGSMGlyph glyph) {
	UGSM_Code result = generateGlyphCode();

	memcpy(UGSM[result], glyph, UGSMGlyphHeight);

	UGSMSize++;

	return result;
}

UGSMGlyph* Font_getGlyph(UGSM_Code glyphCode) {
	if (!checkGlyphCodeIsReserved(glyphCode))
		ERROR_throw(UGSM_GLYPH_NOT_RESERVED_BUT_WE_TRY_USE);
	
	assert

	return &UGSM[glyphCode];
}

bool Font_checkGlyphCodeIsReserved(UGSM_CharacterCode code) {
	return checkBit(UGSMreserveTable[getByteIndex(code)], getBitIndex(code));
}

void reserveGlyphCode(UGSM_CharacterCode code) {
	if (UGSMcheckGlyphCodeIsReserved(code)) // check for reserved
		ERROR_throw(ERROR_GLYPH_CODE_RESERVED); // if the glyph is reserved, then we issue the corresponding error

	else enableBit(&UGSMreserveTable[getByteIndex(code)], getBitIndex(code));
}

void freeGlyphCode(UGSM_CharacterCode code) {
	if (UGSMcheckGlyphCodeIsReserved(code)) // check for reserved
		disableBit(&UGSMreserveTable[getByteIndex(code)], getBitIndex(code));

	else ERROR_throw(ERROR_GLYPH_CODE_NOT_RESERVED); // if the glyph is not reserved, then we issue the corresponding error
}

UGSM_CharacterCode getFreeSpaceForGlyph() {
	uint16 i = 0;

	for (; UGSMreserveTable[i] >= 255; i++);

	if (i <= 128) {
		UGSM_CharacterCode bitIndex = 0;

		while (UGSMreserveTable[i] & (1 << bitIndex)) bitIndex++;

		return i * 8 + bitIndex;
	}

	warn(ALL_GLYPHS_ARE_RESERVED_WARNING);

	return 0;
}

Font_ReserveCode generateGlyphCode() {
	Font_ReserveCode glyphCode = getFreeSpaceForGlyph();

	reserveGlyphCode(glyphCode);

	return glyphCode;
}