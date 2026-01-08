#include "charset/font.h"

#include "core/types/basic_types.h"

#include "core/modules/high-level/std.h"

#include "core/modules/low-level/bcd.h"

#include "core/modules/types/warning.h"

#include "core/error.h"

static uint8 FONT_reserveTable[128] = { 0 }; // bitset for check reservations font code

AbsoluteSize UGSMSize = 0;

bool UGSMcheckGlyphCodeIsReserved(UGSM_CharacterCode code) {
	return checkBit(UGSMreserveTable[getByteIndex(code)], getBitIndex(code));
}

void reserveGlyphCode(UGSM_CharacterCode code) {
	if (UGSMcheckGlyphCodeIsReserved(code)) // check for reserved
		ERROR_throw(GLYPH_CODE_RESERVED_ERROR); // if the glyph is reserved, then we issue the corresponding error

	else enableBit(&UGSMreserveTable[getByteIndex(code)], getBitIndex(code));
}

void freeGlyphCode(UGSM_CharacterCode code) {
	if (UGSMcheckGlyphCodeIsReserved(code)) // check for reserved
		disableBit(&UGSMreserveTable[getByteIndex(code)], getBitIndex(code));

	else ERROR_throw(GLYPH_CODE_NOT_RESERVED_ERROR); // if the glyph is not reserved, then we issue the corresponding error
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

UGSM_CharacterCode generateGlyphCode() {
	UGSM_CharacterCode glyphCode = getFreeSpaceForGlyph();

	reserveGlyphCode(glyphCode);

	return glyphCode;
}
