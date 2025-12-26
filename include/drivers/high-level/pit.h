#ifndef _PIT_H
#define _PIT_H

#include "drivers/low-level/base/idt.h"

#include "core/time.h"

#define standardFreq 1000 // 1 millisecond

void PITInit();

void PITSetFreq(uint16 freq);

void tick(Registers* regs);

void sleepTime(Time delay);

#endif