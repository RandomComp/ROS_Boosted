#include "charset/ugsm.h"

#include "core/std.h"

#include "core/types.h"

#include "core/error.h"

#include "charset/glyph.h"

#include "charset/ascii.h"

#include "charset/rus.h"

#include "drivers/low-level/base/mem.h"

extern UGSMGlyphSetCode ASCIIOffset;

extern UGSMGlyphSetCode RUSOffset;

extern const uint32 columns;

extern int16 x;

extern int16 y;

IUGSM UGSM = { 0 }; // UGSM itself ( единая память для хранения глифов ) ( unified glyph storage memory )

IUGSMSize UGSMSize = 0;

UGSMGlyphSetCode UGSMloadGlyphSet(UGSMGlyphSet glyphSet, UGSMGlyphSetSize length) {
	if (length == 1)
		return UGSMloadGlyph(glyphSet[0]);

	UGSMGlyphSetCode glyphSetCode = getFreeSpaceForGlyph();

	UGSMGlyphSetSize glyphSetEnd = glyphSetCode + length;

	if (glyphSetEnd >= UGSMMaxSize)
		cause(UGSMIncorrectGlyphSetSizeError);

	for (UGSMGlyphCode i = 0; i < length; i++) {
		generateGlyphCode();

		// for (uint8 j = 0; j < UGSMGlyphHeight; j++) {
		// 	UGSM[i + glyphSetCode][j] = glyphSet[i][j];
		// }

		// EXPERIMENTAL, MAY BE NOT WORK!!!

		memcpy(UGSM[i + glyphSetCode], glyphSet[i], UGSMGlyphHeight);
	}

	UGSMSize += length;

	return glyphSetCode;
}

UGSMGlyphCode UGSMloadGlyph(UGSMGlyph glyph) {
	UGSMGlyphCode result = generateGlyphCode();

	// for (uint8 i = 0; i < UGSMGlyphHeight; i++) {
	// 	UGSM[result][i] = glyph[i];
	// }

	// EXPERIMENTAL!!! MAY BE NOT WORK!

	memcpy(UGSM[result], glyph, UGSMGlyphHeight);

	UGSMSize++;

	return result;
}

UGSMGlyph* UGSMgetGlyph(UGSMGlyphCode glyphCode) {
	if (!checkGlyphCodeIsReserved(glyphCode))
		cause(UGSMGlyphNotReservedButWeTryUse);

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
		case ASCII_CHAR_SPACE: 				return UGSM_CHAR_SPACE;
		case ASCII_CHAR_NEW_LINE: 			return UGSM_CHAR_NEW_LINE;
		case ASCII_CHAR_CARRIAGE_RETURN: 	return UGSM_CHAR_CARRIAGE_RETURN;
		case ASCII_CHAR_BACKSPACE: 			return UGSM_CHAR_BACKSPACE;
		case ASCII_CHAR_TAB:  				return UGSM_CHAR_TAB;
	}

	if (c < ASCII_CHAR_SPACE || c > ASCII_CHAR_TILDE)
		return UGSM_CHAR_NULL;

	return ASCIIOffset + (UGSMGlyphCode)(c) - ASCII_CHAR_EXCLAMATION_MARK + UGSM_CHAR_EXCLAMATION_MARK;
}

void UGSMASCIIsetString(uint16 x, uint16 y, int8* str) {
	for (uint16 i = 0; str[i]; i++)
		UGSMASCIIsetChar(x + i, y, str[i]);
}

void UGSMASCIIsetChar(uint16 x, uint16 y, int8 c) {
	if (c >= ASCII_CHAR_SPACE && c <= ASCII_CHAR_TILDE)
		setChar(x, y, UGSMASCIICharToUGSM(c));
}