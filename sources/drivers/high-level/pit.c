#include "drivers/high-level/pit.h"

#include "core/types/basic_types.h"

#include "core/time.h"

#include "drivers/low-level/io/io.h"

#include "drivers/low-level/base/idt.h"

static uint32 currentFreq = 0;

static float millisecondDelta = 1;

static bool bPITInitialized = false;

static Time now;

void PITInit(void) {
	if (bPITInitialized) return;

	IDTInit();

	IDTIRQInstallHandler(0, &tick);

	PITSetFreq(standardFreq);

	bPITInitialized = true;
}

void PITSetFreq(uint16 freq) {
	if (currentFreq == freq) return;

	uint32 divisor = 1193180 / freq;

	out8(0x43, 0x36);

	out8(0x40, (uint8)(divisor & 0xff));

	out8(0x40, (uint8)((divisor >> 8) & 0xff));

	millisecondDelta = (float)standardFreq / (float)freq;
}

void tick(Registers* regs) {
	now += millisecondDelta;

	setTime(now);
}