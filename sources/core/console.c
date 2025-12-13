#include "core/console.h"

#include "core/screen.h"

#include "core/types.h"

// Calculating columns and rows for width and height

const uint32 columns = width / UGSMGlyphWidth;

const uint32 rows = height / UGSMGlyphHeight;

Char consoleBuffer[columns * rows] = { 0 };

