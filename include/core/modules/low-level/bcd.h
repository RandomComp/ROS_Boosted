#ifndef _BCD_H
#define _BCD_H

#include "core/types/basic_types.h"

#include "core/time.h"

#include "core/types/high-level/int_types.h"

#include "core/modules/types/exception.h"

#include "core/types/low-level/error_types.h"

#define ByteBase 1024

#define isValueInRange(value, min, max) ((value) >= (min) && (value) <= (max))

// TODO: Написать единую функцию для преобразования числа в строку, включая дробные.

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
	if (assert(isValueInRange(bitIndex, 0, 64), Exception_fromWarning(WARNING_INVALID_ARGUMENT, Exception_messageFromString("It is not possible to create a bit mask with all bits enabled outside of type. Please check the validity of the input argument bitIndex=[value: uint64].", bitIndex))))
		return 0;

	return bitIndexToMaskU64(bitIndex + 1) - 1;
}

static inline uint32 bitIndexToMaskU32(uint32 bitIndex) {
	if (assert(bitIndex >= 32, Exception_fromWarning(WARNING_INVALID_ARGUMENT, Exception_messageFromString("It is not possible to create a bit mask with enabled bit outside of type. Please check the validity of the input argument bitIndex=[value: uint32].", bitIndex))))
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

static inline uint bitIndexToMaskUInt(uint32 bitIndex) {
	return lshUInt(getUIntOne(), bitIndex);
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

static inline void enableBitU64(uint64* value, uint8 bitIndex) {
	if (bitIndex >= 64); // TODO: Handle error

	*value |= bitIndexToMaskU64(bitIndex);
}

static inline void disableBitU64(uint64* value, uint8 bitIndex) {
	if (bitIndex >= 64); // TODO: Handle error

	*value &= ~bitIndexToMaskU64(bitIndex);
}

static inline bool checkBitU64(uint64 value, uint8 bitIndex) {
	if (bitIndex >= 64) {
		Error_throw(ERROR_INVALID_ARGUMENT);

		return;
	}

	return (value >> bitIndex) & 1;
}

static inline void enableBitUint(uint *value, uint8 bitIndex) {
	if (bitIndex >= value->data) {
		Error_throw(ERROR_INVALID_ARGUMENT);

		return;
	}

	*value = bitOrUInt(*value, bitIndexToMaskUInt(bitIndex));
}

static inline void disableBitU128(uint* value, uint8 bitIndex) {
	if (bitIndex >= value->data) {
		Error_throw(ERROR_INVALID_ARGUMENT);

		return;
	}

	*value = bitAndUInt(*value, bitNotUInt(bitIndexToMaskUInt(bitIndex)));
}

static inline uint8 checkBitUInt(uint value, uint8 bitIndex) {
	if (assert(bitIndex < value.bitDepth, Exception_fromWarning(WARNING_INVALID_ARGUMENT, Exception_messageFromString(Format_string("The bit index [value: uint8] you want to get is out of bounds [value: uint8], the result is always 0.", bitIndex, value.bitDepth))))) {
		return 0;
	}

	uint32* part = nullptr;

	return checkBitU32(*part, bitIndex % 32);
}

static inline uint8 getByteIndex(uint32 value) {
	return value / 8;
}

static inline uint8 getBitIndex(uint32 value) {
	return value % 8;
}

uint32 toBCD(uint32 num);

uint32 fromBCD(uint32 num);

uint64 toBCDU64(uint64 num);

uint64 fromBCDU64(uint64 num);

Hour hourToBCD(Hour hour);

Hour hourFromBCD(Hour hour);

#endif