#include "std/std.h"

#include "std/string/string_types.h"

#include "std/string/char_types.h"

#include "charset/cp437/cp437_types.h"

static bool bSTDInitialized = false;

void STD_Init() {
	if (bSTDInitialized) return;

	

	bSTDInitialized = true;
}

void print(String str) {
	
}

void print_c_str(const c_str str) {
	
}

void printf(String str, ...) {
	
}

void printf_c_str(const c_str str, ...) {
	
}

Char getch() {
	
}

c_char getch_c() {
	
}