#ifndef _RANDOM_OS_STACK_TYPES_H
#define _RANDOM_OS_STACK_TYPES_H

#include "core/types/basic_types.h"

#include "drivers/high-level/virtual_ram_types.h"

typedef struct Stack {
    MemoryRegion* region;

    uint32 stackLength;
} Stack;

#endif