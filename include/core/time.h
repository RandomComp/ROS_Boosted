#ifndef _TIME_H
#define _TIME_H

#include "core/types.h"

#define startOnVirtualMachine true

#define MS_PER_SECOND 1000

#define SECONDS_PER_MINUTE 60

#define MINUTES_PER_HOUR 60

#define HOURS_PER_DAY 24

#define MONTHS_PER_YEAR 12

#define DAYS_PER_YEAR 365.2425

#define MS_PER_MINUTE (SECONDS_PER_MINUTE * MS_PER_SECOND)

#define MS_PER_HOUR (MINUTES_PER_HOUR * MS_PER_MINUTE)

#define MS_PER_DAY (HOURS_PER_DAY * MS_PER_HOUR)

#define MS_PER_YEAR ((int64)DAYS_PER_YEAR * (int64)MS_PER_DAY)

typedef int64 Time;

typedef int16 Millisecond;

typedef int16 Second;

typedef int16 Minute;

typedef int16 Hour;

typedef int32 Day;

typedef int64 Year;

typedef bool ProgressFlag;

typedef uint8 RegisterB;

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

typedef enum DayWeek {
	DAYWEEK_MONDAY, 	// Понедельник
	DAYWEEK_TUESDAY,	// Вторник
	DAYWEEK_WEDNESDAY, 	// Среда
	DAYWEEK_THURSDAY, 	// Четверг
	DAYWEEK_FRIDAY, 	// Пятница
	DAYWEEK_SATURDAY, 	// Суббота
	DAYWEEK_SUNDAY		// Воскресенье
} DayWeek;

typedef enum Season {
	SEASON_WINTER, 	// Зима
	SEASON_SPRING, 	// Весна
	SEASON_SUMMER, 	// Лето
	SEASON_AUTUMN 	// Осень
} Season;

void TimeInit();

int64 convert(int64 value, int64 maxValue, int64 divisor);

Millisecond getMillisecond(Time time);

Second getSecond(Time time);

Minute getMinute(Time time);

Hour getHour(Time time);

Day getDaysPerMonth(Year year, Month month);

Day getDay(Time time);

Day getYearDay(Time time);

DayWeek getDayWeek(Time time);

Month getMonth(Time time);

Season getSeason(Time time);

Year getYear(Time time);

Time getAbsoluteTimeToday(Time time);

bool isLeapYear(Year year);

void updateProgressFlag();

void updateRegisterB();

int8 binaryX8ValueToRTCFormatedIfNecessary(int8 value);

Hour binaryHourToRTCFormatedIfNecessary(Hour hour);

Year binaryYearToRTCFormatedIfNecessary(Year year);

Time binaryTimeToRTCFormatedIfNecessary(Time time);

int8 binaryX8ValueFromRTCFormatedIfNecessary(int8 value);

Hour binaryHourFromRTCFormatedIfNecessary(Hour hour);

Year binaryYearFromRTCFormatedIfNecessary(Year year);

Time binaryTimeFromRTCFormatedIfNecessary(Time time);

void setRTCTime(Time time);

Time loadRTCTime(void);

#endif