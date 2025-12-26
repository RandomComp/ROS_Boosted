#include "core/std.h"

#include "charset/ugsm.h"

#include "core/console.h"

#include "core/char.h"

static bool bSTDInitialized = false;

void STDInit() {
	if (bSTDInitialized) return;

	

	bSTDInitialized = true;
}

void printf(String str, ...) {
	
}

Char getch() {
    
}