#include "charset/charset.h"

#include "core/types/basic_types.h"

#include "charset/types/ugsm_types.h"

#include "charset/types/ascii_types.h"

bool Charset_UGSMGlyphIsControlCharacter(UGSM_CharacterCode glyphCode) {
	return glyphCode >= UGSM_CHAR_NULL && glyphCode <= UGSM_CHAR_TAB;
}

bool Charset_UGSMGlyphIsLetter(UGSM_CharacterCode _glyphCode) {
	UGSM_CharacterCode glyphCode = Charset_UGSMGlyphToLowerCase(_glyphCode);

	return 	(glyphCode >= UGSM_CHAR_A) && (glyphCode <= UGSM_CHAR_Z) ||
			(glyphCode >= UGSM_CHAR_RUS_A) && (glyphCode <= UGSM_CHAR_RUS_YA);
}

bool Charset_UGSMGlyphIsDigit(UGSM_CharacterCode glyphCode) {
	return (glyphCode >= UGSM_CHAR_0) && (glyphCode <= UGSM_CHAR_9);
}

bool Charset_UGSMGlyphIsLetterOrDigit(UGSM_CharacterCode glyphCode) {
	return Charset_UGSMGlyphIsLetter(glyphCode) || Charset_UGSMGlyphIsDigit(glyphCode);
}

UGSM_CharacterCode Charset_UGSMGlyphToUpperCase(UGSM_CharacterCode glyphCode) {
	if ((glyphCode >= UGSM_CHAR_A) && (glyphCode <= UGSM_CHAR_Z))
		return glyphCode - UGSM_CHAR_A + UGSM_CHAR_BIG_A;

	else if ((glyphCode >= UGSM_CHAR_RUS_A) && (glyphCode <= UGSM_CHAR_RUS_YA))
		return glyphCode - UGSM_CHAR_RUS_A + UGSM_CHAR_RUS_BIG_A;

	return glyphCode;
}

UGSM_CharacterCode Charset_UGSMGlyphToLowerCase(UGSM_CharacterCode glyphCode) {
	if ((glyphCode >= UGSM_CHAR_BIG_A) && (glyphCode <= UGSM_CHAR_BIG_Z))
		return glyphCode - UGSM_CHAR_BIG_A + UGSM_CHAR_A;

	else if ((glyphCode >= UGSM_CHAR_RUS_BIG_A) && (glyphCode <= UGSM_CHAR_RUS_BIG_YA))
		return glyphCode - UGSM_CHAR_RUS_BIG_A + UGSM_CHAR_RUS_A;

	return glyphCode;
}