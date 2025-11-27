#ifndef _PIT_H
#define _PIT_H

#include "drivers/low-level/base/idt.h"

#include "core/time.h"

#define standardFreq 500 // one millisecond

void PITInit(void);

void PITSetFreq(uint32 freq);

void tick(struct Registers* regs);

void sleepMilliseconds(Millisecond delay);

void sleepSeconds(Second delay);

void sleepMinutes(Minute delay);

void sleepHours(Hour delay);

void sleepAbsoluteTimeToday(AbsoluteTimeToday delay);

void sleepYearDays(YearDay delay);

void sleepDecades(Decade delay);

void sleepMonthes(Month delay);

void sleepSeasons(Season delay);

void sleepYears(Year delay);

void sleepCenturies(Century delay);

void sleepYears4Digits(Year4Digits delay);

void sleepTime(struct Time delay);

#endif