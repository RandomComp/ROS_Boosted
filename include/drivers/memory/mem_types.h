#ifndef _RANDOM_OS_MEM_TYPES
#define _RANDOM_OS_MEM_TYPES

#include "core/basic_types.h"

typedef enum MemoryRegionStatus {
	MEMORY_STATUS_FREE = 		0b00000001,
	MEMORY_STATUS_ACTIVE = 		0b00000010,
	MEMORY_STATUS_EXECUTABLE = 	0b00000100,
	MEMORY_STATUS_ENCRYPTED = 	0b00001000
} MemoryRegionStatus;

typedef struct Size {
	uint32 GB, MB, KB, bytes;
} Size;

typedef struct MemoryRegionHeader {
	size_t regionSize;

	MemoryRegionStatus regionStatus;
} MemoryRegionHeader;

typedef struct MemoryRegion {
	MemoryRegionHeader header;

	void* memory;
} MemoryRegion;

#endif