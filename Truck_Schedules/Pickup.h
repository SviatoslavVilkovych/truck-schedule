#pragma once
#include "DayTime.h"
#include <string>

using std::string;

class Pickup
{
public:
	string carrierName;
	DayTime time;
	Pickup(const string &name, DayTime pickupTime) { carrierName = name; time = pickupTime; }
	string getPickup() { return carrierName + ", " + time.toString() + "\n"; }
};



