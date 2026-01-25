#include "drivers/memory/ram.h"

#include "core/basic_types.h"

#include "drivers/multiboot/multiboot_types.h"

#include "std/std.h"

#include "math/bit_math.h"

#include "math/math.h"

#include "exceptions/exception.h"

static size_t absoluteSizeInBytes = 0;

static bool initialized = false;

void RAM_Init(size_t size) {
	if (initialized) return;

	absoluteSizeInBytes = 0;

	for (uint32 i = 0; i < bootInfo->mmap_length; i += sizeof(struct multibootMMapEntry)) {
		multibootMMapEntry* mapEntry = (struct multibootMMapEntry*)(bootInfo->mmap_addr + i);
		
		if (mapEntry->type != MULTIBOOT_MEMORY_AVAILABLE) continue;

		absoluteSizeInBytes += mapEntry->len_low;
	}

	initialized = true;
}

void* malloc(size_t size) {
	MemoryRegionStatus status = 0;

	if (status == 0) return 0;

	status |= MEMORY_STATUS_ACTIVE;
}

void* realloc(void* addr, size_t size) {
	
}

size_t getAbsoluteRAMSize() {
	return absoluteSizeInBytes;
}

void MEM_showSize(Size size) {
	if (size.GB != 0) {
		printf("[fg: green][value: u32] gigabytes\n", size.GB);
	}

	if (size.MB != 0) {
		printf("[fg: green][value: u32] megabytes\n", size.MB);
	}

	if (size.KB != 0) {
		printf("[fg: green][value: u32] kilobytes\n", size.KB);
	}

	if (size.bytes != 0) {
		printf("[fg: green][value: u32] bytes\n", size.bytes);
	}
}

void free(void* region) {
	
}

bool RAM_isValidAndActiveMemoryRegion(void* addr) {
	if (addr <= sizeof(MemoryRegion)) return false;

	MemoryRegion* region = addr - sizeof(MemoryRegion);

	MemoryRegionHeader header = region->header;

	return region->memory != 0 && 
			header.regionSize > 0 && 
			header.regionStatus & MEMORY_STATUS_ACTIVE;
}