#include "time/time.h"

#include "async/asyncio.h"

#include "core/modules/std/std.h"

#include "drivers/time/pit.h"

#include "drivers/memory/ram.h"

#include "drivers/io/io.h"

#include "drivers/time/cmos.h"

static Time now;

static bool bTimeInitialized = false;

const static Day numberDaysOfMonthes[MONTHS_PER_YEAR] = {
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

	now = Time_convertToTimeStampFromTimeStruct(getRTCTime());

	PITInit();

	bTimeInitialized = true;
}

Time Time_convertToTimeStampFromTimeStruct(TimeStruct time) {
	Time result = time.milliseconds;

	result += time.second * MS_PER_SECOND;

	result += time.minute * MS_PER_MINUTE;

	result += time.hour * MS_PER_HOUR;

	result += time.day * MS_PER_DAY;

	result += getDaysPerMonth(time.year, time.month) * MS_PER_DAY;

	result += time.year * MS_PER_YEAR;

	return result;
}

Millisecond Time_getMillisecond(Time time) {
	return time % MS_PER_SECOND;
}

Second Time_getSecond(Time time) {
	return (time % MS_PER_MINUTE) / MS_PER_SECOND;
}

Minute Time_getMinute(Time time) {
	return (time % MS_PER_HOUR) / MS_PER_MINUTE;
}

Hour Time_getHour(Time time) {
	return (time % MS_PER_DAY) / MS_PER_HOUR;
}

Day Time_getDaysPerMonth(Year year, Month month) {
	if (month == MONTH_FEBRUARY && isLeapYear(year)) return 29;

	return daysPerMonth[month];
}

Day Time_getDaysPerSeason(Year year, Season season) {
	if (season == SEASON_WINTER && isLeapYear(year)) return 29;

	Day result = 0;

	for (Day i = 0; i < MONTHS_PER_YEAR; i++) {

	}
}

Day Time_getDay(Time time) {
	Day daysPerMonth = Time_getDaysPerMonth(Time_getYear(time), Time_getMonth(time));

	return Time_getYearDay(time) % daysPerMonth;
}

Day Time_getYearDay(Time time) {
	return (time % MS_PER_YEAR) / MS_PER_DAY;
}

DayOfWeek Time_getDayOfWeek(Time time) {
	return result % 7;
}

Month Time_getMonth(Time time) {
	time %= MS_PER_YEAR;

	Month month = MONTH_JANUARY;

	Time msPerCurrentMonth = Time_getDaysPerMonth(Time_getYear(time), month) * MS_PER_DAY;

	while (time >= msPerCurrentMonth) {
		month++;

		msPerCurrentMonth = Time_getDaysPerMonth(Time_getYear(time), month) * MS_PER_DAY;
		
		time -= msPerCurrentMonth;
	}

	return month;
}

Season Time_getSeason(Time time) {
	return seasonFromMonth[Time_getMonth(time)];
}

Year Time_getYear(Time time) {
	return convert(time, INT64_MAX, MS_PER_YEAR);
}

Time Time_getAbsoluteTimeToday(Time time) {
	return time % MS_PER_DAY;
}

Time Time_getTimeStampFromTimeStruct(TimeStruct time) {
	Time result = 0;

	result += (int64)time.milliseconds;
	result += (int64)time.second * 	MS_PER_SECOND;
	result += (int64)time.hour * 	MS_PER_HOUR;
	result += (int64)time.day * 	MS_PER_DAY;
	result += (int64)time.month * 	Time_getDaysPerMonth(time.year, time.month) * MS_PER_DAY;
	result += (int64)time.year * 	MS_PER_YEAR;

	return result;
}

// Если год делиться на 4 без остатка, то високосный, если делиться на 100, и не делиться на 400 то не високосный.
bool Time_isLeapYear(Year year) {
	return year % 4 == 0 && !(year % 100 == 0 && year % 400 != 0);
}

TimeStruct Time_binaryTimeToRTCFormatedIfNecessary(TimeStruct time) {
	if (CMOSCheckBit(CMOS_REGISTER_B, REGISTER_B_IS_BINARY_MODE))
		return time;
	
	TimeStruct result = { 0 };

	result.second = toBCDX8(time.second);
	result.minute = toBCDX8(time.minute);
	result.hour = 	hourToBCD(time.hour);
	result.day = 	toBCDX8(time.day);
	result.month = 	toBCDX8(time.month);
	result.year = 	toBCDX16(time.year);

	return result;
}

TimeStruct Time_binaryTimeFromRTCFormatedIfNecessary(TimeStruct time) {
	if (CMOSCheckBit(CMOS_REGISTER_B, REGISTER_B_IS_BINARY_MODE))
		return time;
	
	TimeStruct result = { 0 };

	result.second = fromBCDX8(time.second);
	result.minute = fromBCDX8(time.minute);
	result.hour = 	hourFromBCD(time.hour);
	result.day = 	fromBCDX8(time.day);
	result.month = 	fromBCDX8(time.month);
	result.year = 	fromBCDX16(time.year);

	return result;
}

void Time_set(Time time) {
	now = time;
}

Time Time_get() {
	return now;
}

Time start, msWaiting;

static AsyncResult sleepAwaiter() {
	return (AsyncResult){ 	.bFinished = now - start >= msWaiting, 
							.result = 0 };
}

void Time_sleep(Time time) {
	await(&sleepAwaiter, now, time);
}