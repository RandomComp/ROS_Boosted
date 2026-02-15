#ifndef _RANDOM_OS_CHAR_H
#define _RANDOM_OS_CHAR_H

#include "core/basic_types.h"

#include "std/string/char_fwd.h"

#include "charset/ugsm/ugsm_types.h"

Char* Char_fromASCII(uint8 ch);

Char* Char_fromUGSM(UGSM_Code ch);

Char* Char_new();

#endif