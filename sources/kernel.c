#include "core/types/low-level/multiboot_types.h"

#include "core/modules/high-level/std.h"

#include "core/time.h"

#include "drivers/low-level/base/ram.h"

extern struct Size RAMSize;

static multibootInfo* bootInfo;

void main(uint32 magic, multibootInfo* bootInfoArg) {
	bootInfo = bootInfoArg;

	MEMInit(2 * 1024 * 1024); // 4 MB

	STDInit();

	ASCIIInit();

	TimeInit();

	kprintf("RAM Size is:\n");

	showSize(RAMSize);

	RUSInit();

	KeyboardPS2Init();

	ACPIInit();

	kprintf("OS is booted succesfully!\n");

	clear(0);

	for (;;);
}