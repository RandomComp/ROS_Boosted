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
	[MONTH_NOVEMBER] = 	SEASON_AUTUMN,
	[MONTH_OCTOBER] = 	SEASON_AUTUMN,
	[MONTH_DECEMBER] = 	SEASON_WINTER
};

void TimeInit(void) {
	if (bTimeInitialized) return;

	now = loadRTCTime();

	PITInit();

	bTimeInitialized = true;
}

Day calculateFebruaryNumberDays(Time time) {
	return time.Year % 4 ? 28 : 29;
}

Time calculateAbsoluteTimeToday(Time time) {
	return time % MS_PER_DAY;
}

DayWeek calculateDayWeek(Time time) {
	DayWeek result = ((time.Year - 1) * 365) + (time.Year / 4); // Year * 365.25 = January first

	result--;

	for (Month m = 0; m < time.month; m++)
		result += numberDaysOfMonthes[m];

	result += time.day;

	return result % 7;
}

Day calculateYearDay(Time time) {
	Day result = 0;

	for (Month m = 0; m < time.month; m++)
		result += numberDaysOfMonthes[m];

	result += time.day;

	return result;
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

int8 binaryX8ValueToRTCFormatedIfNecessary(int8 value) {
	if (!(registerB & 0x04))
		return toBCDX8(value);

	return value;
}

Hour binaryHourToRTCFormatedIfNecessary(Hour hour) {
	if (!(registerB & 0x04))
		return hourToBCD(hour);

	return hour;
}

Year binaryYearToRTCFormatedIfNecessary(Year year) {
	if (!(registerB & 0x04))
		return toBCDX16(year);

	return year;
}

Time binaryTimeToRTCFormatedIfNecessary(Time time) {
	if (!(registerB & 0x04)) {
		Time result = newTime();

		result.second = toBCDX8(time.second);

		result.minute = toBCDX8(time.minute);

		result.hour = hourToBCD(time.hour);

		result.day = toBCDX8(time.day);

		result.month = toBCDX8(time.month);

		result.year = toBCDX16(time.year);

		return result;
	}

	return time;
}

int8 binaryX8ValueFromRTCFormatedIfNecessary(int8 value) {
	if (!(registerB & 0x04))
		return fromBCDX8(value);

	return value;
}

Hour binaryHourFromRTCFormatedIfNecessary(Hour hour) {
	if (!(registerB & 0x04))
		return hourFromBCD(hour);

	return hour;
}

Year binaryYearFromRTCFormatedIfNecessary(Year year) {
	if (!(registerB & 0x04))
		return fromBCDX16(year);

	return year;
}

Time binaryTimeFromRTCFormatedIfNecessary(Time time) {
	if (!(registerB & 0x04)) {
		Time result = 0;

		result.second = fromBCDX8(time.second);

		result.minute = fromBCDX8(time.minute);

		result.hour = hourFromBCD(time.hour);

		result.day = fromBCDX8(time.day);

		result.month = fromBCDX8(time.month);

		result.year = fromBCDX16(time.year);

		return result;
	}

	return time;
}

Time newTime(void) {
	Time result;

	result.millisecond = 0;

	result.second = 0;

	result.minute = 0;

	result.hour = 0;

	result.day = 1;

	result.absoluteTimeToday = 0;

	result.dayWeek = 0;

	result.Day = 1;

	result.decade = 0;

	result.month = 0;

	result.season = 0;

	result.year = 0;

	result.century = 0;

	result.Year = 0;

	return result;
}

Time copyTime(Time time) {
	return time;
}

bool timeEquals(Time time, Time time2) {
	return  time.absoluteTimeToday == time2.absoluteTimeToday &&
			time.Day == time2.Day &&
			time.Year == time2.year4Digits;
}

bool timeNotEquals(Time time, Time time2) {
	return  time.absoluteTimeToday != time2.absoluteTimeToday ||
			time.Day != time2.Day ||
			time.Year != time2.year4Digits;
}

bool timeBigThan(Time time, Time time2) {
	if ((time.Year - time2.year4Digits) > 0) return true;

	if ((time.Day - time2.yearDay) > 0) return true;

	return (time.absoluteTimeToday - time2.absoluteTimeToday) > 0;
}

bool timeLessThan(Time time, Time time2) {
	if ((time.Year - time2.year4Digits) < 0) return true;

	if ((time.Day - time2.yearDay) < 0) return true;

	return (time.absoluteTimeToday - time2.absoluteTimeToday) < 0;
}

bool timeBigOrEqualThan(Time time, Time time2) {
	if ((time.Year - time2.year4Digits) >= 0) return true;

	if ((time.Day - time2.yearDay) >= 0) return true;

	return (time.absoluteTimeToday - time2.absoluteTimeToday) >= 0;
}

bool timeLessOrEqualThan(Time time, Time time2) {
	if ((time.Year - time2.year4Digits) <= 0) return true;

	if ((time.Day - time2.yearDay) <= 0) return true;

	return (time.absoluteTimeToday - time2.absoluteTimeToday) <= 0;
}

Time add(Time time, Time time2) {
	Time result = copyTime(time);

	result.millisecond += time2.millisecond;

	result.second += time2.second;

	result.minute += time2.minute;

	result.hour += time2.hour;

	if (result.day > 1 && time2.day > 1)
		result.day += time2.day;

	result.month += time2.month;

	result.Year += time2.year4Digits;

	return calculateVAll(result);
}

Time subtract(Time time, Time time2) {
	Time result = copyTime(time);

	result.millisecond -= time2.millisecond;

	result.second -= time2.second;

	result.minute -= time2.minute;

	result.hour -= time2.hour;

	if (result.day > 1 && time2.day > 1)
		result.day -= time2.day;

	if (result.day == 0)
		result.day = 1;

	result.month -= time2.month;

	result.Year -= time2.year4Digits;

	return calculateVAll(result);
}

void setRTCTime(Time time) {
	if (startOnVirtualMachine) time.hour -= 3;

	time.month++;

	updateRegisterB();

	time = binaryTimeToRTCFormatedIfNecessary(time);

	out8(0x70, 0x00);

	out8(0x71, time.second);


	out8(0x70, 0x02);

	out8(0x71, time.minute);


	out8(0x70, 0x04);

	out8(0x71, time.hour);


	out8(0x70, 0x07);

	out8(0x71, time.day);


	out8(0x70, 0x08);

	out8(0x71, time.month);


	out8(0x70, 0x09);

	out8(0x71, time.year);
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

	return calculateAll(result);
}