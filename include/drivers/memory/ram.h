#ifndef _RANDOM_OS_RAM_H
#define _RANDOM_OS_RAM_H

#include "drivers/memory/mem_types.h"

void RAM_Init(size_t size);

void* malloc(size_t size);

void* realloc(void* addr, size_t size);

void free(void* region);

bool RAM_isValidAndActiveMemoryRegion(MemoryRegion* region);

size_t getAbsoluteRAMSize();

void MEM_showSize(Size size);

#endif