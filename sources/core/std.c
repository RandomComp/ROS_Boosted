#include "core/std.h"

#include "core/types/string_types.h"

#include "core/types/char_types.h"

#include "core/ascii_types.h"

static bool bSTDInitialized = false;

void STD_Init() {
	if (bSTDInitialized) return;

	

	bSTDInitialized = true;
}

void printf(String str, ...) {
	
}

void kprintf(const ASCII_CharacterCode* str, ...) {
	
}

Char getch() {
    
}

ASCII_CharacterCode kgetch() {
    
}