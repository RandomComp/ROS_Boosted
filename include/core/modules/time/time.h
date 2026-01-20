#ifndef _RANDOM_OS_TIME_H
#define _RANDOM_OS_TIME_H

#include "core/basic_types.h"

#include "time/time_types.h"

#define startOnVirtualMachine true

void TimeInit();

Time Time_convertToTimeStampFromTimeStruct(TimeStruct timeFrom);

Millisecond Time_getMillisecond(Time time);

Second Time_getSecond(Time time);

Minute Time_getMinute(Time time);

Hour Time_getHour(Time time);

Day Time_getDaysPerMonth(Year year, Month month);

Day Time_getDaysPerSeason(Year year, Season season);

Day Time_getDay(Time time);

Day Time_getYearDay(Time time);

DayOfWeek Time_getDayOfWeek(Time time);

Month Time_getMonth(Time time);

Season Time_getSeason(Time time);

Year Time_getYear(Time time);

Time Time_getAbsoluteTimeToday(Time time);

bool Time_isLeapYear(Year year);

TimeStruct Time_binaryTimeToRTCFormatedIfNecessary(TimeStruct time);

TimeStruct Time_binaryTimeFromRTCFormatedIfNecessary(TimeStruct time);

void Time_set(Time time);

Time Time_get();

#endif