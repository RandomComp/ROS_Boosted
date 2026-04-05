#ifndef _R_OS_TIME_TYPES_H
#define _R_OS_TIME_TYPES_H

#include "core/basic_types.h"

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

typedef int64 Millisecond;

typedef int64 Second;

typedef int64 Minute;

typedef int64 Hour;

typedef int64 Day;

typedef int64 Year;

typedef enum Month {
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
	Second second;
	Minute minute;
	Hour hour;
	Day day;
	Month month;
	Year year;
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

#endif