#ifndef _RANDOM_OS_RAM_H
#define _RANDOM_OS_RAM_H

#include "drivers/memory/mem_types.h"

void RAM_init(multibootInfo* info);

void* malloc(size_t size);

void* realloc(void* addr, size_t size);

void free(void* region);

bool RAM_isValidMemory(void* mem);

size_t RAM_getSize();

#endif