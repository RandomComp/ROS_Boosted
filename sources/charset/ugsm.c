#include "charset/ugsm.h"

#include "charset/ugsm_types.h"

#include "core/std.h"

#include "core/types.h"

#include "core/error.h"

#include "charset/glyph.h"

#include "charset/ascii_types.h"

#include "drivers/low-level/base/ram.h"

byte UGSM[UGSM_MAX_SIZE][UGSM_GLYPH_HEIGHT] = { 0 }; // UGSM itself ( единая память для хранения глифов ) ( unified glyph storage memory )

AbsoluteSize UGSMSize = 0;

uint32 UGSMgetLength(UGSMGlyphCode* str) {
	uint32 result = 0;

	while (*str != UGSM_CHAR_NULL) {
		str++;

		result++;
	}

	return result;
}

UGSMGlyphSetCode UGSMloadGlyphSet(UGSMGlyphSet glyphSet, UGSMGlyphSetSize length) {
	if (length == 1)
		return UGSMloadGlyph(glyphSet[0]);

	UGSMGlyphSetCode glyphSetCode = getFreeSpaceForGlyph();

	UGSMGlyphSetSize glyphSetEnd = glyphSetCode + length;

	if (glyphSetEnd >= UGSMMaxSize)
		ERROR_throw(UGSM_INCORRECT_GLYPH_SET_SIZE_ERROR);

	for (UGSMGlyphCode i = 0; i < length; i++) {
		generateGlyphCode();

		memcpy(UGSM[i + glyphSetCode], glyphSet[i], UGSMGlyphHeight);
	}

	UGSMSize += length;

	return glyphSetCode;
}

UGSMGlyphCode UGSMloadGlyph(UGSMGlyph glyph) {
	UGSMGlyphCode result = generateGlyphCode();

	memcpy(UGSM[result], glyph, UGSMGlyphHeight);

	UGSMSize++;

	return result;
}

UGSMGlyph* UGSMgetGlyph(UGSMGlyphCode glyphCode) {
	if (!checkGlyphCodeIsReserved(glyphCode))
		ERROR_throw(UGSM_GLYPH_NOT_RESERVED_BUT_WE_TRY_USE);

	return &UGSM[glyphCode];
}

void UGSMASCIIputString(int8* str) {
	for (uint16 i = 0; str[i]; i++)
		UGSMASCIIputChar(str[i]);
}

void UGSMASCIIputChar(int8 c) {
	putChar(UGSMASCIICharToUGSM(c));
}

UGSMGlyphCode UGSMASCIICharToUGSM(int8 c) {
	switch (c) {
		case CP437_CHAR_SPACE: 				return UGSM_CHAR_SPACE;
		case CP437_CHAR_NEW_LINE: 			return UGSM_CHAR_NEW_LINE;
		case CP437_CHAR_CARRIAGE_RETURN: 	return UGSM_CHAR_CARRIAGE_RETURN;
		case CP437_CHAR_BACKSPACE: 			return UGSM_CHAR_BACKSPACE;
		case CP437_CHAR_TAB:  				return UGSM_CHAR_TAB;
	}

	if (c < CP437_CHAR_SPACE || c > CP437_CHAR_TILDE)
		return UGSM_CHAR_NULL;

	return (UGSMGlyphCode)(c) - CP437_CHAR_EXCLAMATION_MARK + UGSM_CHAR_EXCLAMATION_MARK;
}

UGSMGlyphCode UGSMdigitToUGSM(uint8 digit) {
	return (digit % 10) + UGSM_CHAR_0;
}

void UGSMASCIIsetString(uint16 x, uint16 y, int8* str) {
	for (uint16 i = 0; str[i]; i++)
		UGSMASCIIsetChar(x + i, y, str[i]);
}

void UGSMASCIIsetChar(uint16 x, uint16 y, int8 c) {
	if (c >= CP437_CHAR_SPACE && c <= CP437_CHAR_TILDE)
		setChar(x, y, UGSMASCIICharToUGSM(c));
}