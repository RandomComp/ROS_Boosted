#include "core/console.h"

#include "charset/ugsm.h"

#include "core/char.h"

#include "core/screen.h"

#include "core/types/basic_types.h"

// Calculating columns and rows for width and height

const uint32 columns = width / UGSMGlyphWidth;

const uint32 rows = height / UGSMGlyphHeight;

Char consoleScreen[columns * rows] = { 0 };

//Buffer stdout = newBuffer(columns * rows * sizeof(Char));

//Buffer stdin = newBuffer(columns * rows * sizeof(Char));

// current position of cursor

static int16 x = 0, y = 0;

static bool showCursor = true;

// foreground and background Color

static uint32 foregroundColor = 0xffffff;

static uint32 backgroundColor = 0x000000;

static bool bLockOut = false; // Lock out for functions putChar, setChar and more

void resetConsole() {
	foregroundColor = 0xffffff;

	backgroundColor = 0x000000;

	x = 0;

	y = 0;
}