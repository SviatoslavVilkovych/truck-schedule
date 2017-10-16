#include "DayTime.h"

DayTime DayTime::operator+(const DayTime& operand) const
{
	DayTime temp(this->day, this->hour, this->minute);

	unsigned int minutesSum = temp.minute + operand.getMinute();
	temp.minute = (minutesSum < 60) ? minutesSum : (minutesSum % 60);

	unsigned int hoursSum = temp.hour + operand.getHour() + minutesSum / 60;
	temp.hour = (hoursSum < 24) ? hoursSum : (hoursSum % 24);

	unsigned int day = ((unsigned)(temp.day) + hoursSum / 24);
	temp.day = (day == 7) ? (Days::Sunday) : (Days)(day);

	return temp;
}
DayTime DayTime::operator+(const int& hours) const
{
	DayTime temp(this->day, this->hour, this->minute);

	unsigned int hoursSum = temp.hour + hours;
	temp.hour = (hoursSum < 24) ? hoursSum : (hoursSum % 24);

	unsigned int day = ((unsigned)(temp.day) + hoursSum / 24);
	temp.day = (day == 7) ? (Days::Sunday) : (Days)(day);

	return temp;
}
DayTime DayTime::operator=(const DayTime& operand)
{
	this->day = operand.day;
	this->hour = operand.hour;
	this->minute = operand.minute;

	return *this;
}
bool DayTime::operator<(const DayTime& operand) const
{
	if (this->day < operand.day)
	{
		return true;
	}
	else if ((this->hour < operand.hour)&&(this->day == operand.day))
	{
		return true;
	}
	else if ((this->minute < operand.minute)&&(this->hour == operand.hour)&&(this->day == operand.day))
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool DayTime::operator==(const DayTime & operand) const
{
	return ((this->day == operand.day) && (this->hour == operand.hour) && (this->minute == operand.minute)) ? true : false;
}
string DayTime::toString()
{
	string temp;

	switch (day)
	{
	case Days::Monday: temp = "Monday";
		break;
	case Days::Tuesday: temp = "Tuesday";
		break;
	case Days::Wednesday: temp = "Wednesday";
		break;
	case Days::Thursday: temp = "Thursday";
		break;
	case Days::Friday: temp = "Friday";
		break;
	case Days::Saturday: temp = "Saturday";
		break;
	case Days::Sunday: temp = "Sunday";
		break;
	}

	temp += (" " + std::to_string(hour) + " " + std::to_string(minute));

	return temp;
}

