#pragma once
#include "DayTime.h"
#include <string>
#include <list>

using std::string;
using std::list;

class ICarrier
{
protected:
	string carrierName;
	list<list<DayTime>> carrierSchedule;
public:
	ICarrier() {};
	virtual ~ICarrier() {};
	virtual void setCarrierName(const string& newName) { carrierName = newName; };
	virtual string getCarrierName() { return carrierName; };
	virtual list<list<DayTime>> getCarrierSchedule() = 0;
	virtual void setCarrierSchedule(const list<list<DayTime>> &newCarrierSchedule) = 0;

};