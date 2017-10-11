#pragma once
#include "header.h"

class StaticClient {
	static DayTime currentTime;
	static DayTime getCurrentTime();
public:
	static list<Pickup> getNextPickups(const std::initializer_list<ICarrier*> &allowableCarriers, const unsigned int &amountOfPickups = PICKUP_AMOUNT, const unsigned int &delayFromNow = DELAY_PICKUP_TIME);
};


