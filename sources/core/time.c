#include "core/time.h"

#include "core/std.h"

#include "charset/format.h"

#include "drivers/high-level/pit.h"

#include "drivers/low-level/base/mem.h"

#include "drivers/low-level/io/io.h"

Time now;

bool bTimeInitialized = false;

ProgressFlag progressFlag;

RegisterB registerB;

const Day numberDaysOfMonthes[12] = {
	31, 28, 31, // January, February? ( The question mark means 28 - 29 february day ( leap year ) ), March

	30, 31, 30, // April, May, June

	31, 31, 30, // Jule, August, September

	31, 30, 31 // October, November, December
};

const Season seasonFromMonth[] = {
	[MONTH_JANUARY] = 	SEASON_WINTER,
	[MONTH_FEBRUARY] = 	SEASON_WINTER,
	[MONTH_MARCH] = 	SEASON_SPRING,
	[MONTH_APRIL] = 	SEASON_SPRING,
	[MONTH_MAY] = 		SEASON_SPRING,
	[MONTH_JUNE] = 		SEASON_SUMMER,
	[MONTH_JULY] = 		SEASON_SUMMER,
	[MONTH_AUGUST] = 	SEASON_SUMMER,
	[MONTH_SEPTEMBER] = SEASON_AUTUMN,
	[MONTH_OCTOBER] = 	SEASON_AUTUMN,
	[MONTH_NOVEMBER] = 	SEASON_AUTUMN,
	[MONTH_DECEMBER] = 	SEASON_WINTER
};

const Day daysPerMonth[] = {
	[MONTH_JANUARY] = 	31,
	[MONTH_FEBRUARY] = 	28,
	[MONTH_MARCH] = 	31,
	[MONTH_APRIL] = 	30,
	[MONTH_MAY] = 		31,
	[MONTH_JUNE] = 		30,
	[MONTH_JULY] = 		31,
	[MONTH_AUGUST] = 	31,
	[MONTH_SEPTEMBER] = 30,
	[MONTH_OCTOBER] = 	31,
	[MONTH_NOVEMBER] = 	30,
	[MONTH_DECEMBER] = 	31
};

void TimeInit(void) {
	if (bTimeInitialized) return;

	now = loadRTCTime();

	PITInit();

	bTimeInitialized = true;
}

int64 convert(int64 value, int64 maxValue, int64 divisor) {
	return (value % maxValue) / divisor;
}

Millisecond getMillisecond(Time time) {
	return convert(time, MS_PER_SECOND, 1);
}

Second getSecond(Time time) {
	return convert(time, MS_PER_MINUTE, MS_PER_SECOND);
}

Minute getMinute(Time time) {
	return convert(time, MS_PER_HOUR, MS_PER_MINUTE);
}

Hour getHour(Time time) {
	return convert(time, MS_PER_DAY, MS_PER_HOUR);
}

Day getDaysPerMonth(Year year, Month month) {
	if (month == MONTH_FEBRUARY && isLeapYear(year)) return 29;

	return daysPerMonth[month];
}

Day getDay(Time time) {
	Day daysPerMonth = getDaysPerMonth(getYear(time), getMonth(time));

	return getYearDay(time) % daysPerMonth;
}

Day getYearDay(Time time) {
	return convert(time, MS_PER_YEAR, MS_PER_DAY);
}

DayWeek getDayWeek(Time time) {
	DayWeek result = (getYear(time) - 1) * DAYS_PER_YEAR;
}

Month getMonth(Time time) {
	Month month = MONTH_UNKNOWN;

	Time msPerCurrentMonth = getDaysPerMonth(getYear(time), month) * MS_PER_DAY;

	while (time >= msPerCurrentMonth) {
		month++;

		msPerCurrentMonth = getDaysPerMonth(getYear(time), month) * MS_PER_DAY;
		
		time -= msPerCurrentMonth;
	}

	return month;
}

Season getSeason(Time time) {
	return seasonFromMonth[getMonth(time)];
}

Year getYear(Time time) {
	return convert(time, INT64_MAX, MS_PER_YEAR);
}

Time getAbsoluteTimeToday(Time time) {
	return time % MS_PER_DAY;
}

// Если год делиться на 4 без остатка, то високосный, если делиться на 100, и не делиться на 400 то не високосный.
bool isLeapYear(Year year) {
	return year % 4 == 0 && !(year % 100 == 0 && year % 400 != 0);
}

uint8 RTCRead() {
	
}

void updateProgressFlag(void) {
	out8(0x70, 0x0a);

	in8(0x71, &progressFlag);

	progressFlag &= 0b10000000;
}

void updateRegisterB(void) {
	out8(0x70, 0x0b);

	in8(0x71, &registerB);
}

Time binaryTimeToRTCFormatedIfNecessary(Time time) {
	if (!(registerB & 0x04)) {
		Time result = 0;

		Year year = getYear(time);

		Month month = getMonth(time);

		result += (int64)toBCDX8(getSecond(time))	* MS_PER_SECOND;

		result += (int64)toBCDX8(getMinute(time))	* MS_PER_MINUTE;

		result += (int64)hourToBCD(getHour(time))	* MS_PER_HOUR;

		result += (int64)toBCDX8(getDay(time))		* MS_PER_DAY;

		result += (int64)toBCDX8(getMonth(time))	* getDaysPerMonth(year, month) * MS_PER_DAY;

		result += (int64)toBCDX16(getYear(time))	* 	MS_PER_YEAR;

		return result;
	}

	return time;
}

Time binaryTimeFromRTCFormatedIfNecessary(Time time) {
	if (!(registerB & 0x04)) {
		Time result = 0;

		result.second = fromBCDX8(getSecond(time));

		result.minute = fromBCDX8(getMinute(time));

		result.hour = hourFromBCD(getHour(time));

		result.day = fromBCDX8(getDay(time));

		result.month = fromBCDX8(getMonth(time));

		result.year = fromBCDX16(getYear(time));

		return result;
	}

	return time;
}

void setRTCTime(Time time) {
	if (startOnVirtualMachine) getHour(time) -= 3;

	getMonth(time)++;

	updateRegisterB();

	time = binaryTimeToRTCFormatedIfNecessary(time);

	out8(0x70, 0x00);

	out8(0x71, getSecond(time));


	out8(0x70, 0x02);

	out8(0x71, getMinute(time));


	out8(0x70, 0x04);

	out8(0x71, getHour(time));


	out8(0x70, 0x07);

	out8(0x71, getDay(time));


	out8(0x70, 0x08);

	out8(0x71, getMonth(time));


	out8(0x70, 0x09);

	out8(0x71, getYear(time));
}

Time loadRTCTime(void) {
	Time result = newTime();

	while (progressFlag) updateProgressFlag();

	uint8 tempSecond = 0;

	out8(0x70, 0x00);

	in8(0x71, &tempSecond);

	result.second = tempSecond;


	uint8 tempMinute = 0;

	out8(0x70, 0x02);

	in8(0x71, &tempMinute);

	result.minute = tempMinute;


	uint8 tempHour = 0;

	out8(0x70, 0x04);

	in8(0x71, &tempHour);

	result.hour = tempHour;

	if (startOnVirtualMachine) result.hour += 3;


	uint8 tempDay = 0;

	out8(0x70, 0x07);

	in8(0x71, &tempDay);

	result.day = tempDay;


	uint8 tempMonth = 0;

	out8(0x70, 0x08);

	in8(0x71, &tempMonth);

	result.month = tempMonth;


	uint8 tempYear = 0;

	out8(0x70, 0x09);

	in8(0x71, &tempYear);

	result.year = (int8)tempYear;

	updateRegisterB();


	result = binaryTimeFromRTCFormatedIfNecessary(result);

	result.month--;
	
	result.century = 20;

	return getAll(result);
}