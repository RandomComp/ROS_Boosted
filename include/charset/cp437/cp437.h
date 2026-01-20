#ifndef _RANDOM_OS_CHARSET_CP437_H
#define _RANDOM_OS_CHARSET_CP437_H

#include "charset/ugsm/ugsm_types.h"

#include "charset/cp437/cp437_types.h"

CP437_Code CP437_fromUGSMChar(UGSM_Code c);

CP437_Code CP437_fromDigit(uint8 digit);

CP437_Code CP437_toUpper(CP437_Code c);

CP437_Code CP437_toLower(CP437_Code c);

bool CP437_IsLetter(CP437_Code c);

bool CP437_IsDigit(CP437_Code c);

#endif