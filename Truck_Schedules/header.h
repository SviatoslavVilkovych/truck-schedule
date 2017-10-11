#pragma once

#include <string>
#include <list>
#include <iostream>
#include <system_error>
#include <ctime>

#include "DayTime.h"

using std::cout;
using std::list;
using std::string;

const int DELAY_PICKUP_TIME = 3;
const int PICKUP_AMOUNT = 2;
enum class Days { Sunday, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday };

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

