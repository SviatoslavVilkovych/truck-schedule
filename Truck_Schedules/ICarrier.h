#pragma once

class ICarrier
{
protected:
	string carrierName;
	list<list<DayTime>> carrierSchedule;
public:
	ICarrier();
	virtual ~ICarrier();
	virtual void setCarrierName(const string& newName) { carrierName = newName; };
	virtual string getCarrierName() { return carrierName; };
	virtual list<list<DayTime>> getCarrierSchedule() = 0;
	virtual void setCarrierSchedule(const list<list<DayTime>> &newCarrierSchedule) = 0;

};