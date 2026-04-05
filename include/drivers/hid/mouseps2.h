#ifndef _R_OS_HID_MOUSE_PS2_H
#define _R_OS_HID_MOUSE_PS2_H

#include "drivers/syscall/idt.h"

void MousePS2Init();

void MousePS2Event(struct Registers* regs);

#endif