#include "std/console.h"

#include "core/basic_types.h"

#include "charset/ugsm/ugsm.h"

#include "std/string/char_fwd.h"

#include "graphics/screen.h"

// Calculating columns and rows for width and height

#define COLUMNS (width / GLYPH_WIDTH)

#define ROWS (height / GLYPH_HEIGHT)

Char* consoleScreen[COLUMNS * ROWS] = { 0 };

//Buffer stdout = newBuffer(columns * rows * sizeof(Char));

//Buffer stdin = newBuffer(columns * rows * sizeof(Char));

// current position of cursor

static size_t x = 0, y = 0;