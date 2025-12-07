#include "core/std.h"

#include "drivers/high-level/vbe.h"

#include "drivers/low-level/base/mem.h"

#include "charset/ugsm.h"

#include "charset/abc.h"

// VBE variables

extern uint32 vidmemaddr; // Choosen VBE mode address base

extern uint32 vidmode; // Choosen VBE mode

extern uint8 vidchannels; // Channels of choosen VBE mode

// Calculating columns and rows for width and height

const uint32 columns = width / UGSMGlyphWidth;

const uint32 rows = height / UGSMGlyphHeight;

// Calculating size in pixels of choosen VBE mode

const uint32 size = width * height;

bool bSTDInitialized = false; // flag for check we initialized the STD

// current position of cursor

int16 x = 0, y = 0;

bool showCursor = true;

// foreground and background Color

uint32 foregroundColor = 0xffffff;

uint32 backgroundColor = 0x000000;

bool bLockOut = false; // Lock out for functions putChar, setChar and more

// buffers

uint32 framebuffer[width][height] = { 0 };

uint32 viewbuffer[width][height] = { 0 };

// handler on overflow of the screen with symbols

void (*overflowSymbolsOnScreen)() = 0;

void (*onClearScreen)() = 0;

void STDInit(void) {
	if (bSTDInitialized) return;

	if (VBESetup(width, height))
		VBESetMode(vidmode | 0x4000);

	bSTDInitialized = true;
}

uint32 getStringLength(UGSMGlyphCode str[6]) {
	uint32 result = 0;

	for (; str[result]; result++);

	return result;
}

void setConsoleCursorPosition(int16 _x, int16 _y) {
	x = _x; y = _y;
}

void setConsoleCursorVisible(bool bVisible) {
	showCursor = bVisible;
}

void setString(uint16 x, uint16 y, UGSMGlyphCode str[6]) {
	for (uint16 i = 0; str[i]; i++)
		setChar(x + i, y, str[i]);
}

void putString(UGSMGlyphCode str[384]) {
	for (uint16 i = 0; str[i]; i++)
		putChar(str[i]);
}

void setChar(uint16 x, uint16 y, UGSMGlyphCode glyphCode) {
	uint8 glyphLine = 0;

	uint16 xp = 0, yp = 0;

	UGSMGlyph* glyph = UGSMgetGlyph(glyphCode);

	for (uint16 i = 0; i < UGSMGlyphHeight; i++) {
		glyphLine = (*glyph)[i];

		yp = i + (y * UGSMGlyphHeight);

		for (uint16 j = 0; j < UGSMGlyphWidth; j++) {
			xp = (UGSMGlyphWidth - 1 - j) + (x * UGSMGlyphWidth);

			framebuffer[xp][yp] = (glyphLine & (1 << j)) ? foregroundColor : backgroundColor;
		}
	}
}

void putChar(UGSMGlyphCode glyphCode) {
	if (UGSMGlyphIsControlCharacter(glyphCode)) {
		uint16 xp = x * UGSMGlyphWidth;

		uint16 yp = y * UGSMGlyphHeight;

		for (uint16 i = 0; i < UGSMGlyphWidth; i++) {
			for (uint16 j = 0; j < UGSMGlyphHeight; j++) {
				framebuffer[xp + i][yp + j] = backgroundColor;
			}
		}

		switch (glyphCode) {
			case UGSM_CHAR_NULL: return;

			case UGSM_CHAR_SPACE: 			x++; break;

			case UGSM_CHAR_NEW_LINE: 		y++; x = 0; break;
			
			case UGSM_CHAR_CARRIAGE_RETURN: x = 0; break;

			case UGSM_CHAR_TAB: 			x += 4; break;
		}
	}

	else {
		uint8 glyphLine = 0;

		uint16 xp = 0, yp = 0;

		UGSMGlyph* glyph = UGSMgetGlyph(glyphCode);

		for (uint16 i = 0; i < UGSMGlyphHeight; i++) {
			glyphLine = (*glyph)[i];

			yp = i + (y * UGSMGlyphHeight);

			for (uint16 j = 0; j < UGSMGlyphWidth; j++) {
				xp = (UGSMGlyphWidth - 1 - j) + (x * UGSMGlyphWidth);

				framebuffer[xp][yp] = (glyphLine & (1 << j)) ? foregroundColor : backgroundColor;
			}
		}

		x++;
	}

	if (x >= columns) {
		x = 0;

		y++;
	}

	if (y >= rows - 1) {
		y--;

		bLockOut = true;

		for (uint16 i = 0; i < rows; i++) {
			for (uint16 j = 0; j < columns; j++) {
				uint16 xp = j * UGSMGlyphWidth;

				uint16 yp = i * UGSMGlyphHeight;

				for (uint16 k = 0; k < UGSMGlyphWidth; k++) {
					for (uint16 l = 0; l < UGSMGlyphHeight; l++) {
						framebuffer[xp + k][yp + l] = framebuffer[xp + k][(yp + l) + UGSMGlyphHeight];
					}
				}
			}
		}

		for (uint16 i = 0; i < width; i++) {
			for (uint16 j = 0; j < UGSMGlyphHeight; j++) {
				framebuffer[i][((height - (UGSMGlyphHeight / 2)) - 1) - j] = backgroundColor;
			}
		}

		bLockOut = false;

		if (overflowSymbolsOnScreen)
			overflowSymbolsOnScreen();
	}
}

void fastClear(uint8 backgroundColor) {
	memset(framebuffer, backgroundColor, sizeof(framebuffer));

	resetConsole();
}

void clear(uint32 backgroundColor) {
	for (uint32 i = 0; i < width; i++) {
		for (uint32 j = 0; j < height; j++) {
			framebuffer[i][j] = backgroundColor;
		}
	}

	resetConsole();
}

void resetConsole() {
	foregroundColor = 0xffffff;

	backgroundColor = 0x000000;

	x = 0;

	y = 0;

	if (onClearScreen) onClearScreen();
}

void swap() {
	// for (uint32 i = 0; i < width; i++) {
	// 	for (uint32 j = 0; j < height; j++) {
	// 		if (viewbuffer[i][j] != framebuffer[i][j]) {
	// 			uint32 posp = (i + (j * width)) * vidchannels;

	// 			*(uint32*)((uint8*)vidmemaddr + posp) = framebuffer[i][j];
				
	// 			viewbuffer[i][j] = framebuffer[i][j];
	// 		}
	// 	}
	// }

	// EXPERIMENTAL CODE!!! MAY BE NOT WORK!

	memcpy((uint8*)vidmemaddr, framebuffer, sizeof(framebuffer));

	memcpy(viewbuffer, framebuffer, sizeof(framebuffer));
}