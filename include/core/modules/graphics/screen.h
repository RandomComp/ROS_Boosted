#ifndef _R_OS_SCREEN_H
#define _R_OS_SCREEN_H

#include "core/basic_types.h"

#define width 800

#define height 600

void ScreenInit();

void fastClear(uint8 backgroundColor);

void clear(uint32 backgroundColor);

void swap();

#endif