#ifndef _TIME_H
#define _TIME_H

#include "core/types.h"

#define startOnVirtualMachine true

#define MS_PER_DAY (uint64)(24 * 60 * 60 * 1000)

#define MS_PER_YEAR (uint64)(365.2425 * MS_PER_DAY)

typedef uint64 Time;

typedef int8 Millisecond;

typedef int8 Second;

typedef int8 Minute;

typedef int8 Hour;

typedef int16 Day;

typedef int32 Year;

typedef bool ProgressFlag;

typedef uint8 RegisterB;

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
	MONTH_NOVEMBER, 	// Ноябрь
	MONTH_OCTOBER, 		// Октябрь
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

Day calculateFebruaryNumberDays(Time time);

uint32 calculateAbsoluteTimeToday(Time time);

DayWeek calculateDayWeek(Time time);

Day calculateYearDay(Time time);

Season calculateSeason(Time time);

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

bool timeEquals(Time time, Time time2);

bool timeNotEquals(Time time, Time time2);

bool timeBigThan(Time time, Time time2);

bool timeLessThan(Time time, Time time2);

bool timeBigOrEqualThan(Time time, Time time2);

bool timeLessOrEqualThan(Time time, Time time2);

Time add(Time time, Time time2);

Time subtract(Time time, Time time2);

void setRTCTime(Time time);

Time loadRTCTime(void);

#endif