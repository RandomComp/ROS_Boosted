#include "core/multiboot.h"

#include "core/std.h"

#include "core/time.h"

#include "core/console.h"

#include "core/screen.h"

#include "drivers/low-level/base/mem.h"

extern const uint32 columns;

extern const uint32 rows;

extern int16 x;

extern int16 y;

extern struct Size RAMSize;

extern uint32 framebuffer[width][height];

extern bool bKeyboardPS2Updated;

extern enum KeyState keyStates[128];

extern enum Scancode updatedKey;

extern AbsoluteSize AbsoluteRAMSizeInBytes;

static multibootInfo* bootInfo;

void main(uint32 magic, struct multibootInfo* bootInfoArg) {
	bootInfo = bootInfoArg;

	STDInit();

	ASCIIInit();

	printf("STD is initialized!\n");

	printf("ASCII is initialized!\n");

	TimeInit();

	printf("Time is initialized!\n");

	MEMInit(2 * 1024 * 1024); // 4 MB

	printf("RAM is initialized!\n");

	printf("RAM Size is:\n");

	showSize(RAMSize);

	RUSInit();

	printf("Russian is initialized!\n");

	KeyboardPS2Init();

	printf("Interrupt for PS/2 keyboard is ready to use!\n");

	ACPIInit();

	printf("ACPI is initialized!\n");

	printf("OS is booted succesfully!\n");

	clear(0);

	while (true) {
		
	}
}