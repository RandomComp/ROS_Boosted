#ifndef _RANDOM_OS_CP437_H
#define _RANDOM_OS_CP437_H

#include "charset/ugsm.h"

#include "charset/cp437_types.h"

void CP437_loadToUGSM();

uint32 CP437_StrGetLength(CP437_CharacterCode* str);

CP437_CharacterCode CP437_UGSMCharToCP437(UGSMGlyphCode c);

CP437_CharacterCode CP437_digitToCP437(uint8 digit);

#endif