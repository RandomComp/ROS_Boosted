#include "core/basic_types.h"

#include "core/async.h"

#include "drivers/low-level/io/io.h"

#include "drivers/low-level/io/cmos.h"

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

static bool registerAAwaiter() {
	return !CMOSCheckBit(CMOS_REGISTER_A, REGISTER_A_UPDATE_IN_PROGRESS);
}

TimeStruct getRTCTime(void) {
	TimeStruct result = { 0 };

	await(&registerAAwaiter);

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