#include "charset/glyph.h"

#include "core/types.h"

#include "core/std.h"

#include "core/format.h"

#include "core/warning.h"

#include "core/error.h"

uint8 UGSMreserveTable[128] = { 0 }; // bitset for check reservations UGSM ( единая память для хранения глифов ) ( unified glyph storage memory )

bool UGSMcheckGlyphCodeIsReserved(UGSMGlyphCode code) {
	return checkBit(UGSMreserveTable[getByteIndex(code)], getBitIndex(code));
}

void reserveGlyphCode(UGSMGlyphCode code) {
	if (UGSMcheckGlyphCodeIsReserved(code)) // check for reserved
		ERROR_throw(GLYPH_CODE_RESERVED_ERROR); // if the glyph is reserved, then we issue the corresponding error

	else enableBit(&UGSMreserveTable[getByteIndex(code)], getBitIndex(code));
}

void freeGlyphCode(UGSMGlyphCode code) {
	if (UGSMcheckGlyphCodeIsReserved(code)) // check for reserved
		disableBit(&UGSMreserveTable[getByteIndex(code)], getBitIndex(code));

	else ERROR_throw(GLYPH_CODE_NOT_RESERVED_ERROR); // if the glyph is not reserved, then we issue the corresponding error
}

UGSMGlyphCode getFreeSpaceForGlyph() {
	uint16 i = 0;

	for (; UGSMreserveTable[i] >= 255; i++);

	if (i <= 128) {
		UGSMGlyphCode bitIndex = 0;

		while (UGSMreserveTable[i] & (1 << bitIndex)) bitIndex++;

		return i * 8 + bitIndex;
	}

	warn(ALL_GLYPHS_ARE_RESERVED_WARNING);

	return 0;
}

UGSMGlyphCode generateGlyphCode() {
	UGSMGlyphCode glyphCode = getFreeSpaceForGlyph();

	reserveGlyphCode(glyphCode);

	return glyphCode;
}