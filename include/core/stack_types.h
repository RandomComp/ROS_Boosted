#ifndef _RANDOM_OS_STACK_TYPES_H
#define _RANDOM_OS_STACK_TYPES_H

#include "core/types.h"

#include "drivers/high-level/vram.h"

typedef struct Stack {
    MemoryRegion* region;
} Stack;

#endif