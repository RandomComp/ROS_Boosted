#include "core/types/basic_types.h"

#include "drivers/high-level/mouseps2.h"

#include "drivers/low-level/base/idt.h"

bool bMousePS2Initialized = false;

void MousePS2Init(void) {
	if (bMousePS2Initialized) return;

	IDTIRQInstallHandler(1, &MousePS2Event);

	bMousePS2Initialized = true;
}

void MousePS2Event(struct Registers* regs) {
	
}