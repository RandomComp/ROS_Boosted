#include "core/types.h"

#include "drivers/low-level/io/io.h"

#include "drivers/low-level/io/cmos.h"

void CMOSWrite(UniversalCMOSCode code, uint8 data) {
	out8(CMOS_ADDRESS_PORT, code);

	out8(CMOS_DATA_PORT, data);
}

uint8 CMOSRead(UniversalCMOSCode code) {
	uint8 result = 0;

	out8(CMOS_ADDRESS_PORT, code);

	in8(CMOS_DATA_PORT, &result);

	return result;
}

bool checkProgressFlag(void) {
	return CMOSRead(CMOS_RTC_REGISTER_A) & (1 << REGISTER_A_UPDATE_IN_PROGRESS);
}

void setRTCTime(TimeStruct time) {
	if (startOnVirtualMachine) time.hours -= 3;

	time.months++;

	time = binaryTimeToRTCFormatedIfNecessary(time);

    Register registerB = CMOSRead(CMOS_RTC_REGISTER_B);

    registerB |= (1 << REGISTER_B_SET);

    CMOSWrite(CMOS_RTC_REGISTER_B, registerB);

	CMOSWrite(CMOS_RTC_SECONDS, time.seconds);

	CMOSWrite(CMOS_RTC_MINUTES, time.minutes);

	CMOSWrite(CMOS_RTC_HOURS, time.hours);

	CMOSWrite(CMOS_RTC_DAY_OF_MONTH, time.days);

	CMOSWrite(CMOS_RTC_MONTHS, time.months);

	CMOSWrite(CMOS_RTC_YEARS, time.years);

    Register registerB = CMOSRead(CMOS_RTC_REGISTER_B);

    registerB &= ~(1 << REGISTER_B_SET);

    CMOSWrite(CMOS_RTC_REGISTER_B, registerB);
}

TimeStruct getRTCTime(void) {
	TimeStruct result = { 0 };

	while (CMOSRead(CMOS_RTC_REGISTER_B));

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