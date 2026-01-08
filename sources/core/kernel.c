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

void main(uint32 magic, multibootInfo* bootInfoArg) {
	bootInfo = bootInfoArg;

	STDInit();

	ASCIIInit();

	kprintf("STD is initialized!\n");

	kprintf("ASCII is initialized!\n");

	TimeInit();

	kprintf("Time is initialized!\n");

	MEMInit(2 * 1024 * 1024); // 4 MB

	kprintf("RAM is initialized!\n");

	kprintf("RAM Size is:\n");

	showSize(RAMSize);

	RUSInit();

	kprintf("Russian is initialized!\n");

	KeyboardPS2Init();

	kprintf("Interrupt for PS/2 keyboard is ready to use!\n");

	ACPIInit();

	kprintf("ACPI is initialized!\n");

	kprintf("OS is booted succesfully!\n");

	clear(0);

	while (true) {
		
	}
}