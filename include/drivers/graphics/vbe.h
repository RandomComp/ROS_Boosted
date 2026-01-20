#ifndef _RANDOM_OS_VBE_H
#define _RANDOM_OS_VBE_H

#include "core/basic_types.h"

#include "drivers/high-level/vbe_types.h"

VbeInfoBlock* VBEGetGeneralInfo(void);

ModeInfoBlock* VBEGetModeInfo(uint32 mode);

bool VBESetMode(uint32 mode);

bool VBESetup(uint16 w, uint16 h);

#endif