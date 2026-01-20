#ifndef _RANDOM_OS_STD_H
#define _RANDOM_OS_STD_H

#include "core/basic_types.h"

#include "core/modules/std/string/char_types.h"

#include "core/modules/std/string/string_types.h"

void STD_Init();

void print(String str);

void print_c_str(c_str str);

void printf(String str, ...);

void printf_c_str(c_str str, ...);

Char getch();

#endif