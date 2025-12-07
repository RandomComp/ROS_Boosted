#include "drivers/low-level/base/mem.h"

#include "core/multiboot.h"

#include "core/types.h"

#include "core/std.h"

#include "core/error.h"

#include "core/math.h"

extern struct multibootInfo* bootInfo;

Size RAMSize;

AbsoluteSize AbsoluteRAMSizeInBytes = 0;

Address heapStart = 0;

AbsoluteSize AbsoluteHeapSizeInBytes = 0;

Address freeSpaceStart = 0;

Size heapSize;

bool bMEMInitialized = false;

extern uint32 foregroundColor;

void MEMInit(AbsoluteSize size) {
	if (bMEMInitialized) return;

	for (uint32 i = 0; i < bootInfo->mmap_length; i += sizeof(struct multibootMMapEntry)) {
		multibootMMapEntry* mapEntry = (struct multibootMMapEntry*)(bootInfo->mmap_addr + i);
		
		if (mapEntry->type != 1) continue;

		AbsoluteRAMSizeInBytes += mapEntry->len_low;

		AbsoluteRAMSizeInBytes += (uint64)(mapEntry->len_high) << 32;
	}

	AbsoluteHeapSizeInBytes = size;

	if (AbsoluteHeapSizeInBytes * 2 >= AbsoluteRAMSizeInBytes) {
		cause(MemoryLackError);
	}

	freeSpaceStart = heapStart;

	RAMSize.bytes = AbsoluteRAMSizeInBytes % 1024;

	RAMSize.kb = (AbsoluteRAMSizeInBytes / 1024) % 1024;

	RAMSize.mb = (AbsoluteRAMSizeInBytes / 1024 / 1024) % 1024;

	RAMSize.gb = (AbsoluteRAMSizeInBytes / 1024 / 1024 / 1024) % 1024;

	heapSize.bytes = AbsoluteHeapSizeInBytes % 1024;

	heapSize.kb = (AbsoluteHeapSizeInBytes / 1024) % 1024;

	heapSize.mb = (AbsoluteHeapSizeInBytes / 1024 / 1024) % 1024;

	heapSize.gb = (AbsoluteHeapSizeInBytes / 1024 / 1024 / 1024) % 1024;
}

void* malloc(AbsoluteSize size, MemoryRegionStatus status) {
	Address addr = freeSpaceStart;

	if ((addr + sizeof(MemoryRegionInformation) + size) >= AbsoluteRAMSizeInBytes - freeSpaceStart) {
		//cause(MemoryLackError);
	}

	MemoryRegionInformation* memoryRegionInformation = (MemoryRegionInformation*)(addr);

	memoryRegionInformation->size = size;

	memoryRegionInformation->status = status;

	addr += sizeof(MemoryRegionInformation);

	freeSpaceStart = addr + sizeof(MemoryRegionInformation) + size;

	return (void*)(addr);
}

AbsoluteSize sizeToAbsoluteSize(Size size) {
	return 	size.gb * pow(1024, 3) +
			size.mb * pow(1024, 2) +
			size.kb * 1024 +
			size.bytes;
}

void showSize(Size size) {
	uint32 tempForegroundColor = foregroundColor;

	if (size.gb != 0) {
		putUX16Integer(size.gb);

		foregroundColor = 0x00ff00;

		UGSMASCIIputString(" gigabytes\n");
	}

	if (size.mb != 0) {
		putUX16Integer(size.mb);

		foregroundColor = 0x00ff00;

		UGSMASCIIputString(" megabytes\n");
	}

	if (size.kb != 0) {
		putUX16Integer(size.kb);

		foregroundColor = 0x00ff00;

		UGSMASCIIputString(" kilobytes\n");
	}

	if (size.bytes != 0) {
		putUX16Integer(size.bytes);

		foregroundColor = 0x00ff00;

		UGSMASCIIputString(" bytes\n");
	}

	foregroundColor = tempForegroundColor;
}

void free(void* mem, AbsoluteSize size) {
	size += sizeof(MemoryRegionInformation);

	Address addr = (uint32)(mem) - sizeof(MemoryRegionInformation);

	memset((uint8*)(addr), 0, size);
}