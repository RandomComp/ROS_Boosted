#ifndef _R_OS_MEM_TYPES
#define _R_OS_MEM_TYPES

#include "core/basic_types.h"

typedef enum MemoryStatus {
	MEMORY_STATUS_UNUSED = 		0b00000000,
	MEMORY_STATUS_FREE = 		0b00000001,
	MEMORY_STATUS_ACTIVE = 		0b00000010,
	MEMORY_STATUS_EXECUTABLE = 	0b00000100,
	MEMORY_STATUS_ENCRYPTED = 	0b00001000
} MemoryStatus;

typedef struct Size {
	size_t GB, MB, KB, B;
} Size;

typedef struct MemoryHeader {
	size_t size;

	MemoryStatus status;
} MemoryHeader;

#endif