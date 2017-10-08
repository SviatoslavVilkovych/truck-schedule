// ver 1.
//#include <string>
//#include <list>
//#include <iostream>
//
//enum Day { Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday };
//
//class Carrier {
//	std::string carrierName;
//	std::list<std::list<Date>> weekSchedule;
//
//
//};
//
//class Date {
//	Day day;
//	unsigned short int time;
//
//	void setDate(const Day &day_, const unsigned short &time_) { day = day; time = time_; };
//};
//
//struct Pickup {
//	Date data_time;
//	Carrier carrier;
//};
//
//
//class Client {
//	std::list<Carrier> carriers;
//
//public:
//	void addCarrierSchedule(const Carrier& carrier) {};
//	void findTwoNextPickups(tm data_time) {};
//	//Client();
//	//~Client();
//
//};

// ver 2.
#include <string>
#include <list>
#include <iostream>
struct Pickup
{
	std::string carrierName;
	int time; // need change int to more relavent
};
class ICarrier
{
	std::string carrierName;
	std::list<std::list<int>> carrierSchedule;
public:
	virtual void getCarrierSchedule() = 0;
	virtual void setCarrierSchedule() = 0;
};

class UpsCarrier : public ICarrier
{
	virtual void getCarrierSchedule() { std::cout << "Got!"; };
	virtual void setCarrierSchedule() { std::cout << "WOW"; };
};

void getNextTwoPickups(const std::initializer_list<ICarrier*> &allowableCarriers, const unsigned int &delayFromNow = 3)
{
	for (auto carrier : allowableCarriers)
	{
		carrier->getCarrierSchedule();
	}
}

int main(int argv, char* argc)
{
	UpsCarrier A,B,C;

	getNextTwoPickups({ &A, &B, &C });

	return 0;
}
