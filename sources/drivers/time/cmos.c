#include "drivers/time/cmos.h"

#include "format/bcd.h"

void CMOS_setRTCTime(TimeStruct time) {

}

TimeStruct CMOS_getRTCTime() {
	TimeStruct result = { 0 };

	result.second = CMOS_Read(CMOS_RTC_SECONDS);
	result.minute = CMOS_Read(CMOS_RTC_MINUTES);
	result.hour = 	CMOS_Read(CMOS_RTC_HOURS);
	result.day = 	CMOS_Read(CMOS_RTC_DAY_OF_MONTH);
	result.month = 	CMOS_Read(CMOS_RTC_MONTHS);
	result.year = 	CMOS_Read(CMOS_RTC_YEARS);

	if (!CMOS_CheckBit(CMOS_REGISTER_B, CMOS_REGISTER_B_IS_BINARY_MODE)) {
		result.second = fromBCDU32(result.second);

		result.minute = fromBCDU32(result.minute);

		
	}

	return result;
}