#include "core/time.h"

#include "core/std.h"

#include "charset/format.h"

#include "drivers/high-level/pit.h"

#include "drivers/low-level/base/mem.h"

#include "drivers/low-level/io/io.h"

#include "drivers/low-level/io/cmos.h"

Time now;

bool bTimeInitialized = false;

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

	now = convertToTimeStampFromTimeStruct(getRTCTime());

	PITInit();

	bTimeInitialized = true;
}

int64 convertAndDivide(int64 value, int64 maxValue, int64 divisor) {
	return (value % maxValue) / divisor;
}

int64 convertAndMultiply(int64 value, int64 maxValue, int64 multiplier) {
	return (value * multiplier) % maxValue;
}

Time convertToTimeStamp(TimeUnit timeUnit, int64 value, bool isLeapYear) {
	switch(timeUnit) {
		case TIMEUNIT_MILLISECONDS: 		return value;
		case TIMEUNIT_SECONDS:				return value * MS_PER_SECOND;
		case TIMEUNIT_MINUTES:				return value * MS_PER_MINUTE;
		case TIMEUNIT_HOURS:				return value * MS_PER_HOUR;
		case TIMEUNIT_ABSOLUTE_TIME_TODAY:	return value % MS_PER_DAY;
		case TIMEUNIT_DAY_OF_WEEK:			return value * MS_PER_DAY;
		case TIMEUNIT_DAY_OF_MONTH:			return value * MS_PER_DAY;
		case TIMEUNIT_MONTHS:				return getDaysPerMonth(isLeapYear, value % MONTHS_PER_YEAR) * (value / MONTHS_PER_YEAR) * MS_PER_DAY;
		case TIMEUNIT_SEASON:				return ;
		case TIMEUNIT_YEAR_DAY:				return value * 1;
		case TIMEUNIT_YEARS:				return value * 1;
	}
}

Time convertToTimeStampFromTimeStruct(TimeStruct time) {

}

Millisecond getMillisecond(Time time) {
	return convertAndDivide(time, MS_PER_SECOND, 1);
}

Second getSecond(Time time) {
	return convertAndDivide(time, MS_PER_MINUTE, MS_PER_SECOND);
}

Minute getMinute(Time time) {
	return convertAndDivide(time, MS_PER_HOUR, MS_PER_MINUTE);
}

Hour getHour(Time time) {
	return convertAndDivide(time, MS_PER_DAY, MS_PER_HOUR);
}

Day getDaysPerMonth(bool bIsLeapYear, Month month) {
	if (month == MONTH_FEBRUARY && bIsLeapYear) return 29;

	return daysPerMonth[month];
}

Day getDaysPerSeason(bool bIsLeapYear, Season season) {
	if (season == SEASON_WINTER && bIsLeapYear) return 29;

	
}

Day getDay(Time time) {
	Day daysPerMonth = getDaysPerMonth(getYear(time), getMonth(time));

	return getYearDay(time) % daysPerMonth;
}

Day getYearDay(Time time) {
	return convertAndDivide(time, MS_PER_YEAR, MS_PER_DAY);
}

DayOfWeek getDayOfWeek(Time time) {
	DayOfWeek result = (getYear(time) - 1) * DAYS_PER_YEAR;


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

Time getTimeStampFromTimeStruct(TimeStruct time) {
	Time result = 0;

	result += (int64)time.milliseconds;

	result += (int64)time.seconds * MS_PER_SECOND;

	result += (int64)time.hours * 	MS_PER_HOUR;

	result += (int64)time.days * 	MS_PER_DAY;

	result += (int64)time.months * 	getDaysPerMonthFromTimeStruct(time) * MS_PER_DAY;

	result += (int64)time.years * MS_PER_YEAR;

	return result;
}

Day getDaysPerMonthFromTimeStruct(TimeStruct time) {
	return getDaysPerMonth(isLeapYear(time.years), time.months);
}

Day getYearDayFromTimeStruct(TimeStruct time) {
	Day result = 0;

	for (Month month = MONTH_JANUARY; month < time.months; month++)
		result += getDaysPerMonth(isLeapYear(time.years), month);

	result += time.days;

	return result;
}

DayOfWeek getDayOfWeekFromTimeStruct(TimeStruct time) {
	
}

Season getSeasonFromTimeStruct(TimeStruct time) {

}

Time getAbsoluteTimeTodayFromTimeStruct(TimeStruct time) {

}

// Если год делиться на 4 без остатка, то високосный, если делиться на 100, и не делиться на 400 то не високосный.
bool isLeapYear(Year year) {
	return year % 4 == 0 && !(year % 100 == 0 && year % 400 != 0);
}

TimeStruct binaryTimeToRTCFormatedIfNecessary(TimeStruct time) {
	if (!(CMOSCheckBit(CMOS_REGISTER_B, REGISTER_B_IS_BINARY_MODE))) {
		TimeStruct result = { 0 };

		result.seconds = 	toBCDX8(time.seconds);

		result.minutes = 	toBCDX8(time.minutes);

		result.hours = 		hourToBCD(time.hours);

		result.days = 		toBCDX8(time.days);

		result.months = 	toBCDX8(time.months);

		result.years = 		toBCDX16(time.years);

		return result;
	}

	return time;
}

TimeStruct binaryTimeFromRTCFormatedIfNecessary(TimeStruct time) {
	if (!(CMOSCheckBit(CMOS_REGISTER_B, REGISTER_B_IS_BINARY_MODE))) {
		TimeStruct result = { 0 };

		result.seconds = fromBCDX8(time.seconds);

		result.minutes = fromBCDX8(time.minutes);

		result.hours = hourFromBCD(time.hours);

		result.days = fromBCDX8(time.days);

		result.months = fromBCDX8(time.months);

		result.years = fromBCDX16(time.years);

		return result;
	}

	return time;
}