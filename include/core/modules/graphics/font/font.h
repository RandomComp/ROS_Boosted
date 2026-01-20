#ifndef _RANDOM_OS_FONT_H
#define _RANDOM_OS_FONT_H

#include "core/basic_types.h"

#include "core/modules/graphics/font/font_types.h"

bool Font_checkReserveCodeIsReserved(Font_ReserveCode glyphCode);

void Font_reserveReserveCode(Font_ReserveCode glyphCode);

void Font_freeReserveCode(Font_ReserveCode glyphCode);

Font_ReserveCode Font_generateReserveCode();

#endif