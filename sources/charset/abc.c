#include "charset/abc.h"

#include "core/types.h"

#include "charset/ugsm.h"

#include "charset/ascii.h"

#include "charset/rus.h"

extern UGSMGlyphSetCode ASCIIOffset;

extern UGSMGlyphSetCode RUSOffset;

bool UGSMGlyphIsControlCharacter(UGSMGlyphCode glyphCode) {
	return glyphCode >= UGSM_CHAR_SPACE && glyphCode <= UGSM_CHAR_TAB;
}

bool UGSMGlyphIsLetter(UGSMGlyphCode _glyphCode) {
	UGSMGlyphCode glyphCode = UGSMGlyphToLowerCase(_glyphCode);

	return  (glyphCode >= UGSM_CHAR_A) && (glyphCode <= UGSM_CHAR_Z);
}

bool UGSMGlyphIsDigit(UGSMGlyphCode glyphCode) {
	return (glyphCode >= 19) && (glyphCode <= 28);
}

bool UGSMGlyphIsLetterOrDigit(UGSMGlyphCode glyphCode) {
	return UGSMGlyphIsLetter(glyphCode) || UGSMGlyphIsDigit(glyphCode);
}

UGSMGlyphCode UGSMGlyphToUpperCase(UGSMGlyphCode glyphCode) {
	return ((glyphCode >= (ASCIIOffset + UGSM_CHAR_A)) && (glyphCode <= (ASCIIOffset + UGSM_CHAR_Z))) ?
			(glyphCode - ENGLISH_LETTERS_NUMBER) :
			glyphCode;
}

UGSMGlyphCode UGSMGlyphToLowerCase(UGSMGlyphCode glyphCode) {
	return ((glyphCode >= (ASCIIOffset + UGSM_CHAR_BIG_A)) && (glyphCode <= (ASCIIOffset + UGSM_CHAR_BIG_Z))) ?
			(glyphCode + ENGLISH_LETTERS_NUMBER) :
			glyphCode;
}