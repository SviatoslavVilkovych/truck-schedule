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

using std::cout;
using std::list;
using std::string;
const int DELAY_PICKUP_TIME = 3;
const int PICKUP_AMOUNT = 2;

enum Day { Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday};
class Time {
	
public:
	unsigned short int hour;
	unsigned short int minutes;

};
class DateTime {
	Day day;
	Time time;
	DateTime operator+(Time operand) const { DateTime temp; temp.time = this->time+operand.}
};
struct Pickup
{
	string carrierName;
	int time; // need change int to more relavent
	Pickup(const string &name, int pickupTime) { carrierName = name; time = pickupTime; }
	string getPickup() { return carrierName + ", " + std::to_string(time) + "\n"; }
};
class ICarrier
{
protected:
	string carrierName;
	list<list<int>> carrierSchedule;
public:
	ICarrier() { cout << "ICarrier constuctor called\n"; }
	virtual list<list<int>> getCarrierSchedule() = 0;
	virtual void setCarrierSchedule(const list<list<int>> &newCarrierSchedule) = 0;
	virtual ~ICarrier() { cout << "ICarrier destructor called\n"; };
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

class Client {
	DateTime currentTime;
public:
	// Will be great to generalize allowableCarriers to any of containers.
	list<Pickup> getNextPickups(const std::initializer_list<ICarrier*> &allowableCarriers, const unsigned int &amountOfPickups = PICKUP_AMOUNT, const unsigned int &delayFromNow = DELAY_PICKUP_TIME)
	{
		list<Pickup> nextPickups;

		for (auto carrier : allowableCarriers)
		{
			auto weekendSchedule = carrier->getCarrierSchedule();
		}
	}
};
int main(int argv, char* argc)
{

	ICarrier *C = new UpsCarrier();

	list<Pickup> Z = getNextPickups({ C });
	for (auto pickups : Z)
	{
		cout << pickups.getPickup();
	}

	delete C;

	return 0;
}
