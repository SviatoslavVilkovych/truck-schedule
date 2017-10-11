// WHAT SHOULD I DO
/*
 * finish realization of getNextPickUp
 * write unit tests
 * add comments
 * look at the code one more time and drop little tear...
 */
 
#include <string>
#include <list>
#include <iostream>
#include <system_error>
#include <ctime>

using std::cout;
using std::list;
using std::string;

const int DELAY_PICKUP_TIME = 3;
const int PICKUP_AMOUNT = 2;
enum class Days { Sunday, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday};

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
	else if (this->hour < operand.hour)
	{
		return true;
	}
	else if (this->minute < operand.minute)
	{
		return true;
	}
	else
	{
		return false;
	}
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

struct Pickup
{
	string carrierName;
	DayTime time;
	Pickup(const string &name, DayTime pickupTime) { carrierName = name; time = pickupTime; }
	string getPickup() { return carrierName + ", " + time.toString() + "\n"; }
};

class ICarrier
{
protected:
	string carrierName;
	list<list<DayTime>> carrierSchedule;
public:
	ICarrier() { cout << "ICarrier constuctor called\n"; }
	virtual ~ICarrier() { cout << "ICarrier destructor called\n"; };
	virtual void setCarrierName(const string& newName) { carrierName = newName; };
	virtual string getCarrierName() { return carrierName; };
	virtual list<list<DayTime>> getCarrierSchedule() = 0;
	virtual void setCarrierSchedule(const list<list<DayTime>> &newCarrierSchedule) = 0;

};
class UpsCarrier : public ICarrier
{
public:
	UpsCarrier() { cout << "UpsCarrier construcotr called\n"; }
	UpsCarrier(const string &name, const list<list<DayTime>> &newCarrierSchedule) { carrierName = name;  carrierSchedule = newCarrierSchedule; };
	virtual ~UpsCarrier() { cout << "UpsCarrier destructor called\n"; };
	virtual list<list<DayTime>> getCarrierSchedule() { return carrierSchedule; };
	virtual void setCarrierSchedule(const list<list<DayTime>> &newCarrierSchedule) { carrierSchedule = newCarrierSchedule; };
};

class StaticClient {
	static DayTime currentTime;
	DayTime getCurrentTime();
public:
	static list<Pickup> getNextPickups(const std::initializer_list<ICarrier*> &allowableCarriers, const unsigned int &amountOfPickups = PICKUP_AMOUNT, const unsigned int &delayFromNow = DELAY_PICKUP_TIME);
};
list<Pickup> StaticClient::getNextPickups(const std::initializer_list<ICarrier*> &allowableCarriers, const unsigned int &amountOfPickups, const unsigned int &delayFromNow)
{
	list<Pickup> nextPickups;
	DayTime searchFromDayTime = currentTime + delayFromNow;

	try {
		for (auto carrier : allowableCarriers)
		{
			auto weekendSchedule = carrier->getCarrierSchedule();
			auto daysSchedule = weekendSchedule.begin();
			for (unsigned short int i = 0; (Days)i == searchFromDayTime.getDay(); ++daysSchedule, ++i);
			auto currentDaySchedule = daysSchedule->begin();
			for (int numOfPickup = amountOfPickups; numOfPickup > 0; --numOfPickup, ++currentDaySchedule)
			{
				for (auto iNextPickups = nextPickups.begin(); iNextPickups != nextPickups.end(); ++iNextPickups)
				{
					// examine IF there is faster pickups AND IF this 'faster pickup' not faster then currentTime + delayFromNowTime
					// IF it is faster THEN pop_back last (the slowest) pickup and insert the new one with stored order AND go try another pikcup
					if (*currentDaySchedule < (*iNextPickups).time && searchFromDayTime < (*iNextPickups).time)
					{
						nextPickups.pop_back();
						Pickup newPickup((*iNextPickups).carrierName, (*iNextPickups).time);
						nextPickups.insert(iNextPickups, newPickup);
						break;
					}
				}
			}
		}
	}
	catch (const std::system_error& e)
	{
		cout << "Caught system_error with code " << e.code()
			<< " meaning " << e.what() << '\n';
	}
	return nextPickups;
}
DayTime StaticClient::getCurrentTime()
{
	time_t t = time(0);   // get time now
	tm * now = nullptr;
	localtime_s(now, &t);
	DayTime newTime((Days)(now->tm_wday), now->tm_hour, now->tm_min);

	currentTime = newTime;

	return currentTime;
}
DayTime StaticClient::currentTime;
int main(int argv, char* argc)
{
	ICarrier* carrier = new UpsCarrier();
	carrier->setCarrierName("UPS");
	list<list<DayTime>> weekSchedule
	{
		{ new DayTime(Days::Monday,0,0), new DayTime(Days::Monday,12,0) },
		{ new DayTime(Days::Tuesday,0,0), new DayTime(Days::Tuesday,12,0) },
		{ new DayTime(Days::Wednesday,0,0), new DayTime(Days::Wednesday,12,0) },
		{ new DayTime(Days::Thursday,0,0), new DayTime(Days::Thursday,12,0) },
		{ new DayTime(Days::Friday,0,0), new DayTime(Days::Friday,12,0) },
		{ new DayTime(Days::Saturday,12,0)},
		{ new DayTime(Days::Saturday,12,0)}
	};

	carrier->setCarrierSchedule(weekSchedule);
	list<Pickup> nearestPickups = StaticClient::getNextPickups({carrier});

	for (auto pickup : nearestPickups)
	{
		cout << pickup.getPickup();
	}

	delete carrier;

	return 0;
}
