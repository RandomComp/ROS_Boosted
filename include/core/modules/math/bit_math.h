#ifndef _RANDOM_OS_BIT_MATH_H
#define _RANDOM_OS_BIT_MATH_H

#include "core/basic_types.h"

#define ByteBase 1024

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
	if (assert(isValueInRange(bitIndex, 0, 64), Exception_fromWarning(WARNING_INVALID_ARGUMENT, Exception_fromString("It is not possible to create a bit mask with all bits enabled outside of type. Please check the validity of the input argument bitIndex=[value: uint64].", bitIndex))))
		return 0;

	return bitIndexToMaskU64(bitIndex + 1) - 1;
}

static inline uint32 bitIndexToMaskU32(uint32 bitIndex) {
	if (assert(bitIndex >= 32, Exception_fromWarning(WARNING_INVALID_ARGUMENT, Exception_fromString("It is not possible to create a bit mask with enabled bit outside of type. Please check the validity of the input argument bitIndex=[value: uint32].", bitIndex))))
		return 0;

	return 1U << bitIndex;
}

static inline uint64 bitIndexToMaskU64(uint64 bitIndex) {
	if (bitIndex >= 64) {
		Error_throw(ERROR_INVALID_ARGUMENT);

		return;
	}

	return 1ULL << (uint64)bitIndex;
}

static inline void enableBitU8(uint8* value, uint8 bitIndex) {
	if (bitIndex >= 8) {
		Error_throw(ERROR_INVALID_ARGUMENT);

		return;
	}

	*value |= bitIndexToMaskU8(bitIndex);
}

static inline void disableBitU8(uint8* value, uint8 bitIndex) {
	if (bitIndex >= 8) {
		Error_throw(ERROR_INVALID_ARGUMENT);

		return;
	}

	*value &= ~bitIndexToMaskU8(bitIndex);
}

static inline bool checkBitU8(uint8 value, uint8 bitIndex) {
	if (bitIndex >= 32) {
		Error_throw(ERROR_INVALID_ARGUMENT);

		return;
	}

	return (value >> bitIndex) & 1;
}

static inline void enableBitU16(uint16* value, uint8 bitIndex) {
	if (bitIndex >= 16) {
		Error_throw(ERROR_INVALID_ARGUMENT);

		return;
	}

	*value |= bitIndexToMaskU16(bitIndex);
}

static inline void disableBitU16(uint16* value, uint8 bitIndex) {
	if (bitIndex >= 16) {
		Error_throw(ERROR_INVALID_ARGUMENT);

		return;
	}

	*value &= ~bitIndexToMaskU16(bitIndex);
}

static inline bool checkBitU16(uint16 value, uint8 bitIndex) {
	if (bitIndex >= 16) {
		Error_throw(ERROR_INVALID_ARGUMENT);

		return;
	}

	return (value >> bitIndex) & 1;
}

static inline void enableBitU32(uint32* value, uint8 bitIndex) {
	if (bitIndex >= 32) {
		Error_throw(ERROR_INVALID_ARGUMENT);

		return;
	}

	*value |= bitIndexToMaskU32(bitIndex);
}

static inline void disableBitU32(uint32* value, uint8 bitIndex) {
	if (bitIndex >= 32) {
		Error_throw(ERROR_INVALID_ARGUMENT);

		return;
	}

	*value &= ~bitIndexToMaskU32(bitIndex);
}

static inline uint32 checkBitU32(uint32 value, uint8 bitIndex) {
	if (bitIndex >= 32) {
		Error_throw(ERROR_INVALID_ARGUMENT);

		return;
	}

	return (value >> bitIndex) & 1;
}

#endif