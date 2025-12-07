#include "core/types.h"

#include "drivers/low-level/io/io.h"

#include "drivers/low-level/io/cmos.h"

void CMOSWrite(UniversalCMOSCode code, uint8 data) {
	out8(CMOS_ADDRESS_PORT, code);

	out8(CMOS_DATA_PORT, data);
}

uint8 CMOSRead(UniversalCMOSCode code) {
	out8(CMOS_ADDRESS_PORT, code);

	return in8(CMOS_DATA_PORT);
}

void CMOSEnableBit(UniversalCMOSCode code, uint8 bitIndex) {
	CMOSWrite(code, CMOSRead(code) | (1 << bitIndex));
}

void CMOSDisableBit(UniversalCMOSCode code, uint8 bitIndex) {
	CMOSWrite(code, CMOSRead(code) & ~(1 << bitIndex));
}

bool CMOSCheckBit(UniversalCMOSCode code, uint8 bitIndex) {
	return CMOSRead(code) & (1 << bitIndex);
}

void setRTCTime(TimeStruct time) {
	if (startOnVirtualMachine) time.hours -= 3;

	time.months++;

	time = binaryTimeToRTCFormatedIfNecessary(time);

	CMOSEnableBit(CMOS_REGISTER_B, REGISTER_B_TIME_SET);

	CMOSWrite(CMOS_RTC_SECONDS, 		time.seconds);

	CMOSWrite(CMOS_RTC_MINUTES, 		time.minutes);

	CMOSWrite(CMOS_RTC_HOURS, 			time.hours);

	CMOSWrite(CMOS_RTC_DAY_OF_MONTH, 	time.days);

	CMOSWrite(CMOS_RTC_MONTHS, 			time.months);

	CMOSWrite(CMOS_RTC_YEARS, 			time.years);

	CMOSDisableBit(CMOS_REGISTER_B, REGISTER_B_TIME_SET);
}

TimeStruct getRTCTime(void) {
	TimeStruct result = { 0 };

	while (CMOSRead(CMOS_REGISTER_A) & (1 << REGISTER_A_UPDATE_IN_PROGRESS));

	result.seconds = CMOSRead(CMOS_RTC_SECONDS);

	result.minutes = CMOSRead(CMOS_RTC_MINUTES);

	result.hours = CMOSRead(CMOS_RTC_HOURS);

	result.days = CMOSRead(CMOS_RTC_DAY_OF_MONTH);

	result.months = CMOSRead(CMOS_RTC_MONTHS);

	result.years = CMOSRead(CMOS_RTC_YEARS);

	result = binaryTimeFromRTCFormatedIfNecessary(result);

	result.months--; // Потому что RTC дает месяца в диапазоне 1-12, а система представляет в 0-11

	return result;
}