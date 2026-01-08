#ifndef _STD_H
#define _STD_H

#include "core/types/basic_types.h"

#include "core/types/high-level/char_types.h"

#include "core/types/high-level/string_types.h"

#include "charset/types/ascii_types.h"

void STD_Init();

void printf(String str, ...);

void kprintf(const ASCII_CharacterCode* str, ...);

Char getch();

#endif