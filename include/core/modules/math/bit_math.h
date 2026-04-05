#ifndef _R_OS_BIT_MATH_H
#define _R_OS_BIT_MATH_H

#include "core/basic_types.h"

#include "std/std.h"

#include "math/math.h"

#define ByteBase 1024

#define GET_BYTE(x, index) (((x) >> (index * 8)) & 0xFF)

static inline uint32 BitsToBytes(uint32 bits) {
	return bits / 8;
}

static inline uint32 KBToMB(uint32 KB) {
	return KB / ByteBase;
}

static inline uint32 MBToGB(uint32 MB) {
	return MB / ByteBase;
}

static inline uint32 BytesToBits(uint32 bytes) {
	return bytes * 8;
}

static inline uint32 KBToBytes(uint32 KB) {
	return KB * ByteBase;
}

static inline uint32 MBToKB(uint32 MB) {
	return KBToBytes(MB * ByteBase);
}

static inline uint32 GBToMB(uint32 GB) {
	return MBToKB(GB * ByteBase);
}

static inline uint32 MBToBytes(uint32 MB) {
	return KBToBytes(MBToKB(MB));
}

static inline uint32 GBToBytes(uint32 GB) {
	return MBToBytes(GBToMB(GB));
}

static inline uint32 BytesToKB(uint32 bytes) {
	return bytes / ByteBase;
}

static inline uint32 BytesToMB(uint32 bytes) {
	return KBToMB(BytesToKB(bytes));
}

static inline uint32 BytesToGB(uint32 bytes) {
	return MBToGB(BytesToMB(bytes));
}

static inline uint64 makeIdentityMaskForU64(uint64 bitIndex) {
	if (!inRangeU64(bitIndex, 0, 64)) {
		klog(LOG_ERROR, "It is not possible to create a bit mask with all bits enabled " 
				"outside of type. Please check the validity of the input argument "
				"bitIndex=[value: u64]", bitIndex);

		return 0;
	}

	return bitIndexToMaskU64(bitIndex + 1) - 1;
}

static inline uint32 bitIndexToMaskU32(uint32 bitIndex) {
	if (!inRangeU32(bitIndex, 0, 32)) {
		klog(LOG_WARNING, "Cannot create a bitmask with a bit outside the specified type "
				"u32 enabled. Please verify that the input argument "
				"bitIndex=[value: u32] is valid.", bitIndex
		);

		return 0;
	}

	return 1U << bitIndex;
}

static inline uint64 bitIndexToMaskU64(uint64 bitIndex) {
	if (!inRangeU64(bitIndex, 0, 64)) {
		klog(LOG_WARNING, "Cannot create a bitmask with a bit outside the specified type "
				"u64 enabled. Please verify that the input argument "
				"bitIndex=[value: u64] is valid.", bitIndex
		);

		return 0;
	}

	return 1ULL << (uint64)bitIndex;
}

static inline ErrorCode enableBitU8(uint8* value, uint8 bitIndex) {
	if (!inRangeU8(bitIndex, 0, 8)) {
		klog(LOG_WARNING, "Cannot enable a bit outside the specified u8 type. "
				"Please ensure that the input argument "
				"bitIndex=[value: u8] is valid.", bitIndex
		);

		return CODE_FAIL;
	}

	*value |= bitIndexToMaskU8(bitIndex);
}

static inline ErrorCode disableBitU8(uint8* value, uint8 bitIndex) {
	if (!inRangeU8(bitIndex, 0, 8)) {
		klog(LOG_WARNING, "Cannot disable a bit outside the specified u8 type. "
				"Please ensure bitIndex=[value: u8] is valid.", bitIndex
		);

		return CODE_FAIL;
	}

	*value &= ~bitIndexToMaskU8(bitIndex);
}

static inline bool checkBitU8(uint8 value, uint8 bitIndex) {
	return (value >> bitIndex) & 1;
}

static inline void enableBitU16(uint16* value, uint8 bitIndex) {
	if (!inRangeU8(bitIndex, 0, 16)) {
		klog(LOG_WARNING,
			"Cannot enable a bit outside the specified u16 type. "
			"Please ensure bitIndex=[value: u8] is valid.", bitIndex
		);

		return 0;
	}

	*value |= bitIndexToMaskU16(bitIndex);
}

static inline void disableBitU16(uint16* value, uint8 bitIndex) {
	if (!inRangeU8(bitIndex, 0, 16)) {
		klog(LOG_WARNING,
			"Cannot disable a bit outside the specified u16 type. "
			"Please ensure bitIndex=[value: u8] is valid.", bitIndex
		);

		return 0;
	}

	*value &= ~bitIndexToMaskU16(bitIndex);
}

static inline bool checkBitU16(uint16 value, uint8 bitIndex) {
	return (value >> bitIndex) & 1;
}

static inline void enableBitU32(uint32* value, uint8 bitIndex) {
	if (!inRangeU8(bitIndex, 0, 32)) {
		klog(LOG_WARNING,
			"Cannot enable a bit outside the specified u32 type. "
			"Please ensure bitIndex=[value: u8] is valid.", bitIndex
		);

		return 0;
	}

	*value |= bitIndexToMaskU32(bitIndex);
}

static inline void disableBitU32(uint32* value, uint8 bitIndex) {
	if (!inRangeU8(bitIndex, 0, 32)) {
		klog(LOG_WARNING,
			"Cannot disable a bit outside the specified u32 type. "
			"Please ensure bitIndex=[value: u8] is valid.", bitIndex
		);

		return 0;
	}

	*value &= ~bitIndexToMaskU32(bitIndex);
}

static inline bool checkBitU32(uint32 value, uint8 bitIndex) {
	return (value >> bitIndex) & 1;
}

#endif