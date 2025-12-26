#ifndef _STD_H
#define _STD_H

#include "charset/glyph.h"

#include "charset/ugsm.h"

#include "core/types.h"

#include "core/char.h"

#include "core/console.h"

#include "core/screen.h"

void STDInit();

void printf(String str, ...);

Char getch();

#endif