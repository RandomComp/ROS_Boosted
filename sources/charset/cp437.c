#include "charset/cp437.h"

#include "charset/ugsm.h"

bool bASCIILoadedInitialized = false;

void ASCIIloadToUGSM() {
	if (bASCIILoadedInitialized) return;

	UGSMGlyphSet CP437 = {
		#include "charset/cp437.charset"
	};

	UGSMloadGlyphSet(CP437, 107); // loading ASCII to UGSM

	bASCIILoadedInitialized = true;
}

uint32 ASCIIgetLength(CP437_CharacterCode* str) {
	uint32 result = 0;

	while (*str != CP437_CHAR_NULL) {
		str++;

		result++;
	}

	return result;
}

CP437_CharacterCode ASCIIUGSMCharToASCII(UGSMGlyphCode c) {
	switch (c) {
		case UGSM_CHAR_SPACE: 				return CP437_CHAR_SPACE;
		case UGSM_CHAR_NEW_LINE: 			return CP437_CHAR_NEW_LINE;
		case UGSM_CHAR_CARRIAGE_RETURN: 	return CP437_CHAR_CARRIAGE_RETURN;
		case UGSM_CHAR_BACKSPACE: 			return CP437_CHAR_BACKSPACE;
		case UGSM_CHAR_TAB:  				return CP437_CHAR_TAB;
	}

	if (c < UGSM_CHAR_SPACE || c > UGSM_CHAR_TILDE)
		return CP437_CHAR_NULL;

	return (CP437_CharacterCode)(c) - UGSM_CHAR_EXCLAMATION_MARK + CP437_CHAR_EXCLAMATION_MARK;
}

CP437_CharacterCode ASCIIdigitToUGSM(uint8 digit) {
	return (digit % 10) + CP437_CHAR_0;
}