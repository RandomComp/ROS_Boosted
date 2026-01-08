#include "charset/ugsm.h"

#include "charset/types/ugsm_types.h"

#include "core/std.h"

#include "core/types/basic_types.h"

#include "core/error.h"

#include "charset/font.h"

#include "charset/types/ascii_types.h"

#include "drivers/low-level/base/ram.h"

uint32 UGSMgetLength(UGSM_CharacterCode* str) {
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

	for (UGSM_CharacterCode i = 0; i < length; i++) {
		generateGlyphCode();

		memcpy(UGSM[i + glyphSetCode], glyphSet[i], UGSMGlyphHeight);
	}

	UGSMSize += length;

	return glyphSetCode;
}

UGSM_CharacterCode UGSMloadGlyph(UGSMGlyph glyph) {
	UGSM_CharacterCode result = generateGlyphCode();

	memcpy(UGSM[result], glyph, UGSMGlyphHeight);

	UGSMSize++;

	return result;
}

UGSMGlyph* UGSMgetGlyph(UGSM_CharacterCode glyphCode) {
	if (!checkGlyphCodeIsReserved(glyphCode))
		ERROR_throw(UGSM_GLYPH_NOT_RESERVED_BUT_WE_TRY_USE);

	return &UGSM[glyphCode];
}

UGSM_CharacterCode UGSMASCIICharToUGSM(int8 c) {
	switch (c) {
		case CP437_CHAR_SPACE: 				return UGSM_CHAR_SPACE;
		case CP437_CHAR_NEW_LINE: 			return UGSM_CHAR_NEW_LINE;
		case CP437_CHAR_CARRIAGE_RETURN: 	return UGSM_CHAR_CARRIAGE_RETURN;
		case CP437_CHAR_BACKSPACE: 			return UGSM_CHAR_BACKSPACE;
		case CP437_CHAR_TAB:  				return UGSM_CHAR_TAB;
	}

	if (c < CP437_CHAR_SPACE || c > CP437_CHAR_TILDE)
		return UGSM_CHAR_NULL;

	return (UGSM_CharacterCode)(c) - CP437_CHAR_EXCLAMATION_MARK + UGSM_CHAR_EXCLAMATION_MARK;
}

UGSM_CharacterCode UGSMdigitToUGSM(uint8 digit) {
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