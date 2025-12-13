#include "drivers/high-level/pit.h"

#include "core/types.h"

#include "core/time.h"

#include "core/std.h"

#include "charset/colors.h"

#include "drivers/low-level/io/io.h"

#include "drivers/low-level/base/idt.h"

extern Time now;

extern const Day numberDaysOfMonthes[12];

extern const Season seasonsOfMonthes[12];

extern uint16 foregroundColor;

uint32 currentFreq = 0;

float millisecondDelta = 1;

bool bPITInitialized = false;

void (*everyMillisecond)() = 0;

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
}

// bool sleepHandler() {
// 	return (now - past) < delay;
// }

void sleepTime(Time delay) {
	//while () await();

	return;
}