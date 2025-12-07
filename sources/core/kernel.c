#include "core/multiboot.h"

#include "core/std.h"

#include "drivers/high-level/pit.h"

#include "drivers/high-level/keyboardps2.h"

#include "core/time.h"

#include "drivers/low-level/base/mem.h"

#include "charset/ugsm.h"

#include "charset/ascii.h"

#include "charset/rus.h"

#include "drivers/high-level/speaker.h"

#include "core/warning.h"

#include "core/error.h"

#include "core/fatal_error.h"

#include "drivers/high-level/power.h"

#include "drivers/high-level/acpi.h"

#include "RL/lexer.h"

#include "RMAL/lexer.h"

#include "RMAL/parser.h"

extern const uint32 columns;

extern const uint32 rows;

extern int16 x;

extern int16 y;

extern struct Time now;

extern void (*everySecond);

extern void (*overflowSymbolsOnScreen);

extern uint32 foregroundColor;

extern uint32 backgroundColor;

extern struct Size RAMSize;

extern UGSMGlyphSetCode RUSOffset;

extern UGSMGlyphSetCode ASCIIOffset;

extern Opcode opcodes[512];

extern uint32 opcodesLength;

extern uint32 framebuffer[width][height];

extern bool bKeyboardPS2Updated;

extern enum KeyState keyStates[128];

extern enum Scancode updatedKey;

extern Address heapStart;

extern AbsoluteSize AbsoluteRAMSizeInBytes;

extern AbsoluteSize AbsoluteHeapSizeInBytes;

extern struct Size heapSize;

struct multibootInfo* bootInfo;

enum Commands {
	HELP,

	ECHO,

	COLOR,

	PROGRAM,

	SHUTDOWN,

	REBOOT,

	CLEAR
} Commands;

void DrawMenuBar() {
	uint16 tempX = x;

	uint16 tempY = y;

	x = 0;

	y = 0;

	uint32 tempForegroundColor = foregroundColor;

	uint32 tempBackgroundColor = backgroundColor;

	foregroundColor = 0xffffff;

	backgroundColor = 0x800000;

	int8* str = "Random OS";

	uint16 length = 0;

	for (; str[length]; length++);

	putChar(1);

	if (now.day < 10)
		UGSMASCIIputChar('0');

	putX8Integer(now.day);

	UGSMASCIIputChar('.');

	if (now.month < 10)
		UGSMASCIIputChar('0');

	putX8Integer(now.month + 1);

	UGSMASCIIputChar('.');

	uint8 digitsCount = 0;

	for (uint32 tempNum = now.year4Digits; tempNum != 0; tempNum /= 10) 
		digitsCount++;

	for (uint8 i = 0; i < 3 - digitsCount; i++) {
		UGSMASCIIputChar('0');
	}

	putX32Integer(now.year4Digits);

	uint16 pos = (columns / 2) - (length / 2);

	for (uint16 i = x; i < pos; i++) putChar(1);

	UGSMASCIIputString(str);

	for (uint16 i = pos + length; i < columns; i++) putChar(1);

	x = columns - 9;

	y = 0;

	if (now.hour < 10) {
		UGSMASCIIputChar('0');
	}

	putX8Integer(now.hour);

	UGSMASCIIputChar(':');

	if (now.minute < 10) {
		UGSMASCIIputChar('0');
	}

	putX8Integer(now.minute);

	UGSMASCIIputChar(':');

	if (now.second < 10) {
		UGSMASCIIputChar('0');
	}

	putX8Integer(now.second);

	swap();

	foregroundColor = tempForegroundColor;

	backgroundColor = tempBackgroundColor;

	x = tempX;

	y = tempY;
}

void EverySecond(void) {
	DrawMenuBar();
}

void RMALcompileASCII(int8* code) {
	putChar(UGSM_CHAR_SPACE);

	UGSMGlyphCode UGSMCode[384] = { 0 };

	for (uint16 i = 0; code[i]; i++) {
		switch (code[i]) {
			case 32: UGSMCode[i] = 1; break;
			case 10: UGSMCode[i] = 2; break;
			case 13: UGSMCode[i] = 3; break;
			case 9:  UGSMCode[i] = 4; break;
			default: UGSMCode[i] = (UGSMGlyphCode)(code[i] - 33) + ASCIIOffset + 5; break;
		}
	}

	putString(UGSMCode);

	RMALTokenize(UGSMCode);

	RMALTokensView();

	putChar(UGSM_CHAR_NEW_LINE);

	RMALParse();

	RMALCompile();

	putChar(UGSM_CHAR_NEW_LINE);
}

void main(uint32 magic, struct multibootInfo* bootInfoArg) {
	bootInfo = bootInfoArg;

	STDInit();

	ASCIIInit();

	y += 3;

	foregroundColor = 0x00ff00;

	backgroundColor = 0x000000;

	UGSMASCIIputString("STD is initialized!\n");

	UGSMASCIIputString("ASCII is initialized!\n");

	TimeInit();

	UGSMASCIIputString("Time is initialized!\n");

	MEMInit(2 * 1024 * 1024); // 4 MB

	UGSMASCIIputString("RAM is initialized!\n");

	UGSMASCIIputString("RAM Size is:\n");

	showSize(RAMSize);

	UGSMASCIIputString("Heap start is: ");

	putUX32Integer(heapStart);

	putChar(UGSM_CHAR_NEW_LINE);

	UGSMASCIIputString("Heap size is:\n");

	showSize(heapSize);

	RUSInit();

	UGSMASCIIputString("Russian is initialized!\n");

	everySecond = &EverySecond;

	EverySecond();

	KeyboardPS2Init();

	UGSMASCIIputString("Interrupt for PS/2 keyboard is ready to use!\n");

	ACPIInit();

	UGSMASCIIputString("ACPI is initialized!\n");

	UGSMASCIIputString("OS is booted succesfully!\n");

	foregroundColor = 0xffffff;

	backgroundColor = 0x000000;

	//causeFatal(BadTSError);

	while (true) {
		if (bKeyboardPS2Updated) {
			UGSMASCIIputString("Getted ");

			putUX32Integer(updatedKey);

			UGSMASCIIputString(", ");

			putChar(scancodeToUGSM(updatedKey));

			putChar(UGSM_CHAR_NEW_LINE);

			bKeyboardPS2Updated = false;

			swap();
		}
	}

	for (;;);
}