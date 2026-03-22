#include "charset/cp437/cp437.h"

#include "core/basic_types.h"

#include "charset/ugsm/ugsm_types.h"

#include "core/modules/math/math.h"

CP437_Code CP437_fromUGSMChar(UGSM_Code c) {
	switch (c) {
		case UGSM_CHAR_SPACE: 				return CP437_SPACE;
		case UGSM_CHAR_NEW_LINE: 			return CP437_NEW_LINE;
		case UGSM_CHAR_CARRIAGE_RETURN: 	return CP437_CARRIAGE_RETURN;
		case UGSM_CHAR_BACKSPACE: 			return CP437_BACKSPACE;
		case UGSM_CHAR_TAB:  				return CP437_TAB;
	}

	CP437_Code result = (CP437_Code)(c) - UGSM_CHAR_EXCLAMATION_MARK + CP437_EXCLAMATION_MARK;

	if (c < UGSM_CHAR_SPACE || c > UGSM_CHAR_TILDE)
		return CP437_NULL;

	return result;
}

CP437_Code CP437_fromDigit(uint8 digit) {
	return (digit % 10) + CP437_0;
}

CP437_Code CP437_toUpper(CP437_Code c) {
	
}

CP437_Code CP437_toLower(CP437_Code c) {
	
}

bool CP437_IsLetter(CP437_Code c) {

}

bool CP437_IsDigit(CP437_Code c) {

}