#ifndef _RANDOM_OS_SCREEN_H
#define _RANDOM_OS_SCREEN_H

#include "core/types.h"

#define width 800

#define height 600

void ScreenInit();

void fastClear(uint8 backgroundColor);

void clear(uint32 backgroundColor);

void swap();

#endif