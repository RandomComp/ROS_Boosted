#include "core/multiboot.h"

#include "core/std.h"

#include "drivers/high-level/pit.h"

#include "drivers/high-level/keyboardps2.h"

#include "drivers/high-level/mouseps2.h"

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

void main(uint32 magic, struct multibootInfo* bootInfoArg) {
	bootInfo = bootInfoArg;

	STDInit();

	ASCIIInit();

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

	KeyboardPS2Init();

	UGSMASCIIputString("Interrupt for PS/2 keyboard is ready to use!\n");

	ACPIInit();

	UGSMASCIIputString("ACPI is initialized!\n");

	UGSMASCIIputString("OS is booted succesfully!\n");

	foregroundColor = 0xffffff;

	backgroundColor = 0x000000;

	while (true) {
		if (bKeyboardPS2Updated) {
			clear(0x000000);

			putChar(UGSM_CHAR_DOUBLE_QUOTES);

			putChar(scancodeToUGSM(updatedKey));
			
			putChar(UGSM_CHAR_DOUBLE_QUOTES);

			bKeyboardPS2Updated = false;

			swap();
		}
	}
}