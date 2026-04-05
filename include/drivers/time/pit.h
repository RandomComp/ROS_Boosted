#ifndef _R_OS_DRIVER_TIME_PIT_H
#define _R_OS_DRIVER_TIME_PIT_H

#include "drivers/syscall/idt.h"

#include "time/time.h"

#define standardFreq 1000 // 1 millisecond

void PITInit();

void PITSetFreq(uint16 freq);

void tick(Registers* regs);

void sleepTime(Time delay);

#endif