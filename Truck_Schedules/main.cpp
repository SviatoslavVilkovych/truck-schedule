// WHAT SHOULD I DO
/*
 * redefine constructors
 * redefine get/set schedule
 * change intTime to something more relavent
 * provide realization of getNextPickUp
 * write unit tests
 */
 
// ver 2.
#include <string>
#include <list>
#include <iostream>
#include <system_error>
using std::cout;
using std::list;
using std::string;
const int DELAY_PICKUP_TIME = 3;
const int PICKUP_AMOUNT = 2;

enum class Days { Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday};
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
	list<list<int>> carrierSchedule;
public:
	ICarrier() { cout << "ICarrier constuctor called\n"; }
	virtual ~ICarrier() { cout << "ICarrier destructor called\n"; };
	virtual list<list<int>> getCarrierSchedule() = 0;
	virtual void setCarrierSchedule(const list<list<int>> &newCarrierSchedule) = 0;

};

class UpsCarrier : public ICarrier
{
public:
	// temporary class
	UpsCarrier() { cout << carrierName << std::endl << carrierSchedule.size() << std::endl; }
	UpsCarrier(const string &name, const list<list<int>> &newCarrierSchedule) { carrierName = name;  carrierSchedule = newCarrierSchedule; };
	virtual ~UpsCarrier() { cout << "UpsCarrier destructor called\n"; };
	virtual list<list<int>> getCarrierSchedule() { return carrierSchedule; };
	virtual void setCarrierSchedule(const list<list<int>> &newCarrierSchedule) { carrierSchedule = newCarrierSchedule; };
};

class DayTime {
	Days day;
	unsigned short int hour;
	unsigned short int minute;
public:
	Days getDay() { return day; };
	unsigned short int getHour() { return hour; };
	unsigned short int getMinute() { return minute; };

	string toString();

	DayTime(Days day = Days::Monday, int hour = 0, int minute = 0) {};
	DayTime operator+(const DayTime &operand) const;
	DayTime operator=(const DayTime &operand);
};
DayTime DayTime::operator+(const DayTime &operand) const
{
	DayTime temp(this->day, this->hour, this->minute); 

	unsigned int minutesSum = temp.minute + operand.minute;
	temp.minute = (minutesSum < 60) ? minutesSum : (minutesSum % 60);

	unsigned int hoursSum = temp.hour + operand.hour + minutesSum / 60;
	temp.hour = (hoursSum < 24) ? hoursSum : (hoursSum % 24);

	temp.day = (Days)((unsigned)(temp.day) + hoursSum / 24);
	
}
DayTime DayTime::operator=(const DayTime &operand)
{
	this->day = operand.day;
	this->hour = operand.hour;
	this->minute = operand.minute;

	return *this;
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

class Client {
	static DayTime currentTime;
public:
	static list<Pickup> getNextPickups(const std::initializer_list<ICarrier*> &allowableCarriers, const unsigned int &amountOfPickups = PICKUP_AMOUNT, const unsigned int &delayFromNow = DELAY_PICKUP_TIME)
	{
		list<Pickup> nextPickups;
		try {
			for (auto carrier : allowableCarriers)
			{
				auto weekendSchedule = carrier->getCarrierSchedule();
			}
		}
		catch (const std::system_error& e)
		{
			cout << "Caught system_error with code " << e.code()
				 << " meaning " << e.what() << '\n';
		}
		return nextPickups;
	}
};

int main(int argv, char* argc)
{
	ICarrier* C = new UpsCarrier();

	list<Pickup> nearestPickups = Client::getNextPickups();

	for (auto pickup : nearestPickups)
	{
		cout << pickup.getPickup();
	}

	delete C;

	return 0;
}
