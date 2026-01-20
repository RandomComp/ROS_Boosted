#include "charset/ugsm/ugsm.h"

#include "charset/ugsm/ugsm_types.h"

#include "core/basic_types.h"

#include "charset/cp437/cp437_types.h"

UGSM_Code UGSMASCIICharToUGSM(int8 c) {
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

UGSM_Code UGSMdigitToUGSM(uint8 digit) {
	return (digit % 10) + UGSM_CHAR_0;
}