#ifndef _TIME_H
#define _TIME_H

#include "core/types.h"

#define startOnVirtualMachine true

#define MS_PER_SECOND 1000

#define SECONDS_PER_MINUTE 60

#define MINUTES_PER_HOUR 60

#define HOURS_PER_DAY 24

#define DAYS_PER_WEEK 7

#define MONTHS_PER_YEAR 12

#define SEASONS_PER_YEAR 4

#define DAYS_PER_YEAR 365.2425

#define MS_PER_MINUTE	(SECONDS_PER_MINUTE * MS_PER_SECOND)

#define MS_PER_HOUR		(MINUTES_PER_HOUR * MS_PER_MINUTE)

#define MS_PER_DAY		(HOURS_PER_DAY * MS_PER_HOUR)

#define MS_PER_YEAR		((int64)DAYS_PER_YEAR * (int64)MS_PER_DAY)

typedef int64 Time;

typedef int16 Millisecond;

typedef int16 Second;

typedef int16 Minute;

typedef int16 Hour;

typedef int32 Day;

typedef int64 Year;

typedef enum Month {
	MONTH_UNKNOWN = -1, // Неопределенный месяц
	MONTH_JANUARY, 		// Январь
	MONTH_FEBRUARY, 	// Февраль
	MONTH_MARCH, 		// Март
	MONTH_APRIL, 		// Апрель
	MONTH_MAY, 			// Май
	MONTH_JUNE, 		// Июнь
	MONTH_JULY, 		// Июль
	MONTH_AUGUST, 		// Август
	MONTH_SEPTEMBER, 	// Сентябрь
	MONTH_OCTOBER, 		// Октябрь
	MONTH_NOVEMBER, 	// Ноябрь
	MONTH_DECEMBER 		// Декабрь
} Month;

typedef enum DayOfWeek {
	DayOfWeek_MONDAY,		// Понедельник
	DayOfWeek_TUESDAY,		// Вторник
	DayOfWeek_WEDNESDAY, 	// Среда
	DayOfWeek_THURSDAY,		// Четверг
	DayOfWeek_FRIDAY, 		// Пятница
	DayOfWeek_SATURDAY, 	// Суббота
	DayOfWeek_SUNDAY		// Воскресенье
} DayOfWeek;

typedef enum Season {
	SEASON_WINTER, 	// Зима
	SEASON_SPRING, 	// Весна
	SEASON_SUMMER, 	// Лето
	SEASON_AUTUMN 	// Осень
} Season;

typedef struct TimeStruct {
	Millisecond milliseconds;

	Second seconds;

	Minute minutes;

	Hour hours;

	Day days;

	Month months;

	Year years;
} TimeStruct;

typedef enum TimeUnit {
	TIMEUNIT_MILLISECONDS,
	TIMEUNIT_SECONDS,
	TIMEUNIT_MINUTES,
	TIMEUNIT_HOURS,
	TIMEUNIT_ABSOLUTE_TIME_TODAY,
	TIMEUNIT_DAY_OF_WEEK,
	TIMEUNIT_DAY_OF_MONTH,
	TIMEUNIT_MONTHS,
	TIMEUNIT_SEASON,
	TIMEUNIT_YEAR_DAY,
	TIMEUNIT_YEARS
} TimeUnit;

void TimeInit();

int64 convertAndDivide(int64 value, int64 maxValue, int64 divisor);

Time convertToTimeStamp(TimeUnit timeUnit, int64 value, bool isLeapYear);

Time convertToTimeStampFromTimeStruct(TimeStruct timeFrom);

Millisecond getMillisecond(Time time);

Second getSecond(Time time);

Minute getMinute(Time time);

Hour getHour(Time time);

Day getDaysPerMonth(bool bIsLeapYear, Month month);

Day getDaysPerSeason(bool bIsLeapYear, Season season);

Day getDay(Time time);

Day getYearDay(Time time);

DayOfWeek getDayOfWeek(Time time);

Month getMonth(Time time);

Season getSeason(Time time);

Year getYear(Time time);

Time getAbsoluteTimeToday(Time time);

Day getDaysPerMonthFromTimeStruct(TimeStruct time);

Day getYearDayFromTimeStruct(TimeStruct time);

DayOfWeek getDayOfWeekFromTimeStruct(TimeStruct time);

Season getSeasonFromTimeStruct(TimeStruct time);

Time getAbsoluteTimeTodayFromTimeStruct(TimeStruct time);

bool isLeapYear(Year year);

TimeStruct binaryTimeToRTCFormatedIfNecessary(TimeStruct time);

TimeStruct binaryTimeFromRTCFormatedIfNecessary(TimeStruct time);

#endif