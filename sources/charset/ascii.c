#include "charset/ascii.h"

#include "charset/ugsm.h"

bool bASCIILoadedInitialized = false;

void ASCIIloadToUGSM() {
	if (bASCIILoadedInitialized) return;

	UGSMGlyphSet ASCII = {
		#include "charset/ascii.charset"
	};

	UGSMloadGlyphSet(ASCII, 107); // loading ASCII to UGSM
}

uint32 ASCIIgetLength(ASCIIGlyphCode* str) {
	
}

ASCIIGlyphCode ASCIIUGSMCharToASCII(UGSMGlyphCode c) {
	switch (c) {
		case UGSM_CHAR_SPACE: 				return ASCII_CHAR_SPACE;
		case UGSM_CHAR_NEW_LINE: 			return ASCII_CHAR_NEW_LINE;
		case UGSM_CHAR_CARRIAGE_RETURN: 	return ASCII_CHAR_CARRIAGE_RETURN;
		case UGSM_CHAR_BACKSPACE: 			return ASCII_CHAR_BACKSPACE;
		case UGSM_CHAR_TAB:  				return ASCII_CHAR_TAB;
	}

	if (c < UGSM_CHAR_SPACE || c > UGSM_CHAR_TILDE)
		return ASCII_CHAR_NULL;

	return (ASCIIGlyphCode)(c) - UGSM_CHAR_EXCLAMATION_MARK + ASCII_CHAR_EXCLAMATION_MARK;
}

ASCIIGlyphCode ASCIIdigitToUGSM(uint8 digit) {
	return (digit % 10) + ASCII_CHAR_0;
}