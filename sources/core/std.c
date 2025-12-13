#include "core/std.h"

#include "core/screen.h"

#include "charset/ugsm.h"

#include "charset/abc.h"

static bool bSTDInitialized = false;

// current position of cursor

static int16 x = 0, y = 0;

static bool showCursor = true;

// foreground and background Color

static uint32 foregroundColor = 0xffffff;

static uint32 backgroundColor = 0x000000;

static bool bLockOut = false; // Lock out for functions putChar, setChar and more

// handler on overflow of the screen with symbols

void (*overflowSymbolsOnScreen)() = 0;

void (*onClearScreen)() = 0;

void STDInit() {
	if (bSTDInitialized) return;

	

	bSTDInitialized = true;
}



void resetConsole() {
	foregroundColor = 0xffffff;

	backgroundColor = 0x000000;

	x = 0;

	y = 0;

	if (onClearScreen) onClearScreen();
}