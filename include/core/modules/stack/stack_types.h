#ifndef _R_OS_STACK_TYPES_H
#define _R_OS_STACK_TYPES_H

#include "core/basic_types.h"

#include "drivers/high-level/virtual_ram_types.h"

typedef struct Stack {
    MemoryRegion* region;

    uint32 stackLength;
} Stack;

#endif