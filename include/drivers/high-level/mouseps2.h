#ifndef _MOUSEPS2_H
#define _MOUSEPS2_H

#include "drivers/low-level/base/idt.h"

void MousePS2Init(void);

void MousePS2Event(struct Registers* regs);

#endif