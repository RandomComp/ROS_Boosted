#ifndef _RANDOM_OS_STD_H
#define _RANDOM_OS_STD_H

#include "core/basic_types.h"

#include "core/modules/std/string/char_types.h"

#include "core/modules/std/string/string_types.h"

void STD_Init();

void print_str(String str);

void print(c_str str);

void printf_str(String str, ...);

void printf(c_str str, ...);

Char getch();

#endif