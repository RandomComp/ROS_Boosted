#ifndef _RANDOM_OS_MEM_TYPES
#define _RANDOM_OS_MEM_TYPES

#include "core/types/basic_types.h"

typedef uint32 AbsoluteSize;

typedef enum MemoryRegionStatus {
	MEMORY_STATUS_FREE = 		0b00000001,
	MEMORY_STATUS_ACTIVE = 		0b00000010,
	MEMORY_STATUS_READABLE = 	0b00000100,
	MEMORY_STATUS_WRITABLE = 	0b00001000,
	MEMORY_STATUS_EXECUTABLE = 	0b00010000,
	MEMORY_STATUS_ENCRYPTED = 	0b00100000
} MemoryRegionStatus;

typedef struct Size {
	uint32 GB, MB, KB, bytes;
} Size;

typedef struct MemoryRegionHeader {
	AbsoluteSize regionSize;

	MemoryRegionStatus regionStatus;
} MemoryRegionHeader;

typedef struct MemoryRegion {
	MemoryRegionHeader header;

	void* memory;
} MemoryRegion;

#endif