#include "std/string/format.h"

#include "core/basic_types.h"

#include "std/string/string_types.h"

#include "builtins/mem.h"

#include "drivers/memory/ram.h"

String Format_str(String format, ...) {
	
}

c_str Format_c_str(const c_str format, ...) {
	uint32 format_str_len = strlen(format);

	c_str result = malloc(sizeof(c_char) * format_str_len, MEMORY_STATUS_ACTIVE);

	memcpy(result, format, format_str_len);

	
}