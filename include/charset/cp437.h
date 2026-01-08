#ifndef _RANDOM_OS_CP437_H
#define _RANDOM_OS_CP437_H

#include "charset/ugsm.h"

#include "charset/cp437_types.h"

void CP437_loadStandardFont();

uint32 CP437_strGetLength(CP437_CharacterCode* str);

CP437_CharacterCode CP437_fromUGSMChar(UGSM_CharacterCode c);

CP437_CharacterCode CP437_fromDigit(uint8 digit);

#endif