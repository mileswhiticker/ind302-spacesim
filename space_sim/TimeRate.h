#ifndef DEFINES_TIME_H
#define DEFINES_TIME_H

enum TimeRate
{
	PAUSED,
	//
	HOURLY,
	DAILY,
	WEEKLY,
	MONTHLY,
	//
	MAXTIMEVAL
};

#define HOURS_DAY 24
#define DAYS_WEEK 7
#define WEEKS_MONTH 4
#define MONTHS_YEAR 12

#endif	//DEFINES_TIME_H