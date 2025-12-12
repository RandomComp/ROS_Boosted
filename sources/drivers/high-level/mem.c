#include "drivers/low-level/base/mem.h"

#include "core/multiboot.h"

#include "core/types.h"

#include "core/std.h"

#include "core/format.h"

#include "core/error.h"

#include "core/math.h"

extern struct multibootInfo* bootInfo;

Size RAMSize;

AbsoluteSize AbsoluteRAMSizeInBytes = 0;

bool bMEMInitialized = false;

extern uint32 foregroundColor;

void MEMInit(AbsoluteSize size) {
	if (bMEMInitialized) return;

	for (uint32 i = 0; i < bootInfo->mmap_length; i += sizeof(struct multibootMMapEntry)) {
		multibootMMapEntry* mapEntry = (struct multibootMMapEntry*)(bootInfo->mmap_addr + i);
		
		if (mapEntry->type != MULTIBOOT_MEMORY_AVAILABLE) continue;

		AbsoluteRAMSizeInBytes += mapEntry->len_low;
	}

	RAMSize = sizeFromAbsoluteSize(AbsoluteRAMSizeInBytes);
}

MemoryRegion* malloc(AbsoluteSize size, MemoryRegionStatus status) {
	
}

AbsoluteSize sizeToAbsoluteSize(Size size) {
	return 	size.GB * pow(1024, 3) +
			size.MB * pow(1024, 2) +
			size.KB * 1024 +
			size.bytes;
}

Size sizeFromAbsoluteSize(AbsoluteSize size) {
	return (Size){	.bytes 	= size				% ByteBase,
					.KB		= BytesToKB(size) 	% ByteBase,
					.MB		= BytesToMB(size) 	% ByteBase,
					.GB		= BytesToGB(size) 	% ByteBase};
}

void showSize(Size size) {
	uint32 tempForegroundColor = foregroundColor;

	if (size.GB != 0) {
		putUX16Integer(size.GB);

		foregroundColor = 0x00ff00;

		UGSMASCIIputString(" gigabytes\n");
	}

	if (size.MB != 0) {
		putUX16Integer(size.MB);

		foregroundColor = 0x00ff00;

		UGSMASCIIputString(" megabytes\n");
	}

	if (size.KB != 0) {
		putUX16Integer(size.KB);

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

void free(MemoryRegion* region) {
	
}