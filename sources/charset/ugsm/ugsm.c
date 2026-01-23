#include "charset/ugsm/ugsm.h"

#include "charset/ugsm/ugsm_types.h"

#include "core/basic_types.h"

#include "charset/cp437/cp437_types.h"

UGSM_Code UGSM_ASCIICharToUGSM(int8 c) {
	switch (c) {
		case CP437_CHAR_SPACE: 				return UGSM_CHAR_SPACE;
		case CP437_CHAR_NEW_LINE: 			return UGSM_CHAR_NEW_LINE;
		case CP437_CHAR_CARRIAGE_RETURN: 	return UGSM_CHAR_CARRIAGE_RETURN;
		case CP437_CHAR_BACKSPACE: 			return UGSM_CHAR_BACKSPACE;
		case CP437_CHAR_TAB:  				return UGSM_CHAR_TAB;
	}

	if (c < CP437_CHAR_SPACE || c > CP437_CHAR_TILDE)
		return UGSM_CHAR_NULL;

	return (UGSM_Code)(c) - CP437_CHAR_EXCLAMATION_MARK + UGSM_CHAR_EXCLAMATION_MARK;
}

UGSM_Code UGSM_fromDigit(uint8 digit) {
	return (digit % 10) + UGSM_CHAR_0;
}

bool UGSM_GlyphIsControlCharacter(UGSM_Code glyphCode) {
	return glyphCode >= UGSM_CHAR_NULL && glyphCode <= UGSM_CHAR_TAB;
}

bool UGSM_GlyphIsLetter(UGSM_Code _glyphCode) {
	UGSM_Code glyphCode = Charset_UGSMGlyphToLowerCase(_glyphCode);

	return 	(glyphCode >= UGSM_CHAR_A) && (glyphCode <= UGSM_CHAR_Z) ||
			(glyphCode >= UGSM_CHAR_RUS_A) && (glyphCode <= UGSM_CHAR_RUS_YA);
}

bool UGSM_GlyphIsDigit(UGSM_Code glyphCode) {
	return (glyphCode >= UGSM_CHAR_0) && (glyphCode <= UGSM_CHAR_9);
}

bool UGSM_GlyphIsLetterOrDigit(UGSM_Code glyphCode) {
	return Charset_UGSMGlyphIsLetter(glyphCode) || Charset_UGSMGlyphIsDigit(glyphCode);
}

UGSM_Code UGSM_GlyphToUpperCase(UGSM_Code glyphCode) {
	if ((glyphCode >= UGSM_CHAR_A) && (glyphCode <= UGSM_CHAR_Z))
		return glyphCode - UGSM_CHAR_A + UGSM_CHAR_BIG_A;

	else if ((glyphCode >= UGSM_CHAR_RUS_A) && (glyphCode <= UGSM_CHAR_RUS_YA))
		return glyphCode - UGSM_CHAR_RUS_A + UGSM_CHAR_RUS_BIG_A;

	return glyphCode;
}

UGSM_Code UGSM_GlyphToLowerCase(UGSM_Code glyphCode) {
	if ((glyphCode >= UGSM_CHAR_BIG_A) && (glyphCode <= UGSM_CHAR_BIG_Z))
		return glyphCode - UGSM_CHAR_BIG_A + UGSM_CHAR_A;

	else if ((glyphCode >= UGSM_CHAR_RUS_BIG_A) && (glyphCode <= UGSM_CHAR_RUS_BIG_YA))
		return glyphCode - UGSM_CHAR_RUS_BIG_A + UGSM_CHAR_RUS_A;

	return glyphCode;
}