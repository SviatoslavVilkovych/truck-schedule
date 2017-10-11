#include "StaticClient.h"


list<Pickup> StaticClient::getNextPickups(const std::initializer_list<ICarrier*> &allowableCarriers, const unsigned int &amountOfPickups, const unsigned int &delayFromNow)
{
	list<Pickup> nextPickups;
	DayTime searchFromDayTime = getCurrentTime() + delayFromNow;

	try {
		for (auto carrier : allowableCarriers)
		{
			auto weekendSchedule = carrier->getCarrierSchedule();
			auto daysSchedule = weekendSchedule.begin();
			for (unsigned short int i = 0; (Days)i == searchFromDayTime.getDay(); ++daysSchedule, ++i);
			auto currentDaySchedule = daysSchedule->begin();
			// first initialization
			Pickup pickup(carrier->getCarrierName(), (*currentDaySchedule));
			++currentDaySchedule;
			nextPickups.push_back(pickup);
			for (int numOfPickup = amountOfPickups; numOfPickup > 0 && currentDaySchedule != daysSchedule->end(); --numOfPickup, ++currentDaySchedule)
			{
				for (auto iNextPickups = nextPickups.begin(); iNextPickups != nextPickups.end(); ++iNextPickups)
				{
					// examine IF there is faster pickups AND IF this 'faster pickup' not faster then currentTime + delayFromNowTime
					// or we still have free place to put it.
					// IF it is faster THEN pop_back last (the slowest) pickup and insert the new one with stored order AND go try another pikcup
					if ((*currentDaySchedule < (*iNextPickups).time) && (searchFromDayTime < (*iNextPickups).time) || nextPickups.size() < amountOfPickups)
					{
						nextPickups.pop_back();
						Pickup newPickup(carrier->getCarrierName(), (*currentDaySchedule));
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
	tm * now = new tm();
	localtime_s(now, &t);
	DayTime newTime((Days)(now->tm_wday), now->tm_hour, now->tm_min);

	currentTime = newTime;

	return currentTime;
}

DayTime StaticClient::currentTime;
