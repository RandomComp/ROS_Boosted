#ifndef _R_OS_RAM_H
#define _R_OS_RAM_H

#include "drivers/memory/mem_types.h"

void RAM_init(multibootInfo* info);

void* malloc(size_t size);

void* сalloc(size_t cnt, size_t elem_size);

void* realloc(void* addr, size_t size);

void free(void* region);

bool RAM_isValidMemory(void* mem);

size_t RAM_getSize();

#endif