#include "../headers/mem.h"

#include "../headers/multiboot.h"

#include "../headers/types.h"

#include "../headers/std.h"

#include "../headers/error.h"

#include "../headers/math.h"

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

	RAMSize.kilobytes = (AbsoluteRAMSizeInBytes / 1024) % 1024;

	RAMSize.megabytes = (AbsoluteRAMSizeInBytes / 1024 / 1024) % 1024;

	RAMSize.gigabytes = (AbsoluteRAMSizeInBytes / 1024 / 1024 / 1024) % 1024;

	heapSize.bytes = AbsoluteHeapSizeInBytes % 1024;

	heapSize.kilobytes = (AbsoluteHeapSizeInBytes / 1024) % 1024;

	heapSize.megabytes = (AbsoluteHeapSizeInBytes / 1024 / 1024) % 1024;

	heapSize.gigabytes = (AbsoluteHeapSizeInBytes / 1024 / 1024 / 1024) % 1024;
}

void* malloc(AbsoluteSize size, enum MemoryRegionStatus status) {
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
	return 	size.gigabytes * pow(1024, 3) +
			size.megabytes * pow(1024, 2) +
			size.kilobytes * 1024 +
			size.bytes;
}

void showSize(Size size) {
	foregroundColor = 0xffff00;

	if (size.gigabytes != 0) {
		putUX16Integer(size.gigabytes);

		foregroundColor = 0x00ff00;

		UGSMASCIIputString(" gigabytes\n");
	}

	if (size.megabytes != 0) {
		putUX16Integer(size.megabytes);

		foregroundColor = 0x00ff00;

		UGSMASCIIputString(" megabytes\n");
	}

	if (size.kilobytes != 0) {
		putUX16Integer(size.kilobytes);

		foregroundColor = 0x00ff00;

		UGSMASCIIputString(" kilobytes\n");
	}

	if (size.bytes != 0) {
		putUX16Integer(size.bytes);

		foregroundColor = 0x00ff00;

		UGSMASCIIputString(" bytes\n");
	}
}

void free(void* argMem, AbsoluteSize size) {
	size += sizeof(MemoryRegionInformation);

	Address addr = (uint32)(argMem) - sizeof(MemoryRegionInformation);

	uint8* mem = (uint8*)(addr);

	for (Address i = 0; i < size; i++)
		mem[i] = 0;
}