#include "../headers/ugsm.h"

#include "../headers/std.h"

#include "../headers/types.h"

#include "../headers/error.h"

#include "../headers/glyph.h"

#include "../headers/ascii.h"

#include "../headers/rus.h"

extern UGSMGlyphSetCode ASCIIOffset;

extern UGSMGlyphSetCode RUSOffset;

extern const uint32 columns;

extern int16 x;

extern int16 y;

IUGSM UGSM = { 0 }; // UGSM itself ( единая память для хранения глифов ) ( unified glyph storage memory )

IUGSMSize UGSMSize = 0;

UGSMGlyphSetCode UGSMloadGlyphSet(UGSMGlyphSet glyphSet, UGSMGlyphSetSize length) {
	if (length == 1) {
		UGSMloadGlyph(glyphSet[0]);
	}

	UGSMGlyphSetCode glyphSetCode = getFreeSpaceForGlyph();

	UGSMGlyphSetSize glyphSetEnd = glyphSetCode + length;

	if (glyphSetEnd >= UGSMMaxSize)
		cause(UGSMIncorrectGlyphSetSizeError);

	for (UGSMGlyphCode i = 0; i < length; i++) {
		generateGlyphCode();

		for (uint8 j = 0; j < UGSMGlyphHeight; j++) {
			UGSM[i + glyphSetCode][j] = glyphSet[i][j];
		}
	}

	UGSMSize += length;

	return glyphSetCode;
}

UGSMGlyphCode UGSMloadGlyph(UGSMGlyph glyph) {
	UGSMGlyphCode result = generateGlyphCode();

	for (uint8 i = 0; i < UGSMGlyphHeight; i++) {
		UGSM[result][i] = glyph[i];
	}

	UGSMSize++;

	return result;
}

void UGSMcheckGlyphCode(UGSMGlyphCode glyphCode) {
	if (!checkGlyphCodeIsReserved(glyphCode))
		cause(UGSMGlyphNotReservedButWeTryUse);
}

UGSMGlyph* UGSMgetGlyph(UGSMGlyphCode glyphCode) {
	UGSMcheckGlyphCode(glyphCode);

	return &UGSM[glyphCode];
}

void UGSMASCIIputString(int8* str) {
	for (uint16 i = 0; str[i]; i++)
		UGSMASCIIputChar(str[i]);
}

void UGSMASCIIputChar(int8 c) {
	putChar(ASCIICharToUGSM(c));
}

UGSMGlyphCode ASCIICharToUGSM(int8 c) {
	switch (c) {
		case 32: return 1;
		case 10: return 2;
		case 13: return 3;
		case 9:  return 4;
		default: return ASCIIOffset + (UGSMGlyphCode)(c) - 33 + 5;
	}
}

void UGSMASCIIsetString(uint16 x, uint16 y, int8* str) {
	for (uint16 i = 0; str[i]; i++)
		UGSMASCIIsetChar(x + i, y, str[i]);
}

void UGSMASCIIsetChar(uint16 x, uint16 y, int8 c) {
	if (c >= 32 && c <= 126)
		setChar(x, y, (UGSMGlyphCode)(c - 32) + ASCIIOffset + 3);
}