#include "charset/abc.h"

#include "core/types.h"

#include "charset/ugsm.h"

#include "charset/ascii.h"

#include "charset/rus.h"

bool UGSMGlyphIsControlCharacter(UGSMGlyphCode glyphCode) {
	return glyphCode >= UGSM_CHAR_NULL && glyphCode <= UGSM_CHAR_TAB;
}

bool UGSMGlyphIsLetter(UGSMGlyphCode _glyphCode) {
	UGSMGlyphCode glyphCode = UGSMGlyphToLowerCase(_glyphCode);

	return 	(glyphCode >= UGSM_CHAR_A) && (glyphCode <= UGSM_CHAR_Z) ||
			(glyphCode >= UGSM_CHAR_RUS_A) && (glyphCode <= UGSM_CHAR_RUS_YA);
}

bool UGSMGlyphIsDigit(UGSMGlyphCode glyphCode) {
	return (glyphCode >= UGSM_CHAR_0) && (glyphCode <= UGSM_CHAR_9);
}

bool UGSMGlyphIsLetterOrDigit(UGSMGlyphCode glyphCode) {
	return UGSMGlyphIsLetter(glyphCode) || UGSMGlyphIsDigit(glyphCode);
}

UGSMGlyphCode UGSMGlyphToUpperCase(UGSMGlyphCode glyphCode) {
	if ((glyphCode >= UGSM_CHAR_A) && (glyphCode <= UGSM_CHAR_Z))
		return glyphCode - UGSM_CHAR_A + UGSM_CHAR_BIG_A;

	else if ((glyphCode >= UGSM_CHAR_RUS_A) && (glyphCode <= UGSM_CHAR_RUS_YA))
		return glyphCode - UGSM_CHAR_RUS_A + UGSM_CHAR_RUS_BIG_A;

	return glyphCode;
}

UGSMGlyphCode UGSMGlyphToLowerCase(UGSMGlyphCode glyphCode) {
	if ((glyphCode >= UGSM_CHAR_BIG_A) && (glyphCode <= UGSM_CHAR_BIG_Z))
		return glyphCode - UGSM_CHAR_BIG_A + UGSM_CHAR_A;

	else if ((glyphCode >= UGSM_CHAR_RUS_BIG_A) && (glyphCode <= UGSM_CHAR_RUS_BIG_YA))
		return glyphCode - UGSM_CHAR_RUS_BIG_A + UGSM_CHAR_RUS_A;

	return glyphCode;
}