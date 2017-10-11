#pragma once
#include "header.h"

class DayTime {
	Days day;
	unsigned short int hour;
	unsigned short int minute;
public:
	Days getDay() const { return day; };
	unsigned short int getHour() const { return hour; };
	unsigned short int getMinute() const { return minute; };
	string toString();

	DayTime(Days day_ = Days::Sunday, int hour_ = 0, int minute_ = 0) { day = day_; hour = hour_; minute = minute_; };
	DayTime operator+(const DayTime& operand) const;
	DayTime operator+(const int& hours) const;
	DayTime operator=(const DayTime& operand);
	bool operator<(const DayTime& operand) const;
};
