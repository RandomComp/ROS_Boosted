#ifndef _RANDOM_OS_TIME_CMOS_H
#define _RANDOM_OS_TIME_CMOS_H

#include "core/basic_types.h"

#include "time/time_types.h"

#include "drivers/time/cmos_types.h"

#include "math/bit_math.h"

#define CMOS_ADDRESS_PORT 	0x70

#define CMOS_DATA_PORT 		0x71

static inline void CMOS_Write(CMOS_UniversalCode code, uint8 data) {
	out8(CMOS_ADDRESS_PORT, code);

	out8(CMOS_DATA_PORT, data);
}

static inline uint8 CMOS_Read(CMOS_UniversalCode code) {
	out8(CMOS_ADDRESS_PORT, code);

	return in8(CMOS_DATA_PORT);
}

static inline void CMOS_EnableBit(CMOS_UniversalCode code, uint8 bitIndex) {
	uint8 data = CMOS_Read(code);

	enableBitU32(&data, bitIndex);

	CMOS_Write(code, data);
}

static inline void CMOS_DisableBit(CMOS_UniversalCode code, uint8 bitIndex) {
	uint8 data = CMOS_Read(code);

	disableBitU32(&data, bitIndex);

	CMOS_Write(code, data);
}

static inline bool CMOS_CheckBit(CMOS_UniversalCode code, uint8 bitIndex) {
	return checkBitU32(CMOS_Read(code), bitIndex);
}

void CMOS_setRTCTime(TimeStruct time);

TimeStruct CMOS_getRTCTime();

#endif