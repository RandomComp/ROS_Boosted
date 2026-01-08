#include "drivers/low-level/base/ram.h"

#include "core/types/basic_types.h"

#include "core/multiboot.h"

#include "core/std.h"

#include "core/bcd.h"

#include "core/error.h"

#include "core/math.h"

extern struct multibootInfo* bootInfo;

static Size RAM_Size;

static AbsoluteSize RAM_absoluteSizeInBytes = 0;

static bool bMEM_initialized = false;

extern uint32 foregroundColor;

void MEM_Init(AbsoluteSize size) {
	if (bMEM_initialized) return;

	for (uint32 i = 0; i < bootInfo->mmap_length; i += sizeof(struct multibootMMapEntry)) {
		multibootMMapEntry* mapEntry = (struct multibootMMapEntry*)(bootInfo->mmap_addr + i);
		
		if (mapEntry->type != MULTIBOOT_MEMORY_AVAILABLE) continue;

		AbsoluteRAMSizeInBytes += mapEntry->len_low;
	}

	RAMSize = sizeFromAbsoluteSize(AbsoluteRAMSizeInBytes);
}

MemoryRegion* MEM_malloc(AbsoluteSize size, MemoryRegionStatus status) {
	
}

AbsoluteSize getAbsoluteRAMSize() {
	return abs
}

AbsoluteSize MEM_sizeToAbsoluteSize(Size size) {
	return 	size.GB * pow(1024, 3) +
			size.MB * pow(1024, 2) +
			size.KB * 1024 +
			size.bytes;
}

Size MEM_sizeFromAbsoluteSize(AbsoluteSize size) {
	return (Size){	.bytes 	= size				% ByteBase,
					.KB		= BytesToKB(size) 	% ByteBase,
					.MB		= BytesToMB(size) 	% ByteBase,
					.GB		= BytesToGB(size) 	% ByteBase};
}

void MEM_showSize(Size size) {
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
		uint32To(size.bytes);

		foregroundColor = 0x00ff00;

		UGSMASCIIputString(" bytes\n");
	}

	foregroundColor = tempForegroundColor;
}

void MEM_free(MemoryRegion* region) {
	
}

bool MEM_isValidAndActiveMemoryRegion(MemoryRegion* region) {
	MemoryRegionHeader header = region->header;

	return region != 0 && header.regionSize > 0 && header.regionStatus == ;
}