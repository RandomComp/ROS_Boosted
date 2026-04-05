#ifndef _R_OS_STRING_H
#define _R_OS_STRING_H

#include "core/basic_types.h"

#include "std/string/char_fwd.h"

#include "std/string/string_fwd.h"

#include "format/T_types.h"

#include "exceptions/exception.h"

#include "drivers/memory/ram.h"

void String_free(String* str);

void String_cat(String* a, String* b); // Конкатенирует две строки

#endif