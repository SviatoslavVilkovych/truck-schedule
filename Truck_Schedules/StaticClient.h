#pragma once
#include "DayTime.h"
#include "ICarrier.h"
#include "Pickup.h"
#include <list>
#include <iostream>
#include <ctime>

using std::cout;
using std::list;

const int DELAY_PICKUP_TIME = 3;
const int PICKUP_AMOUNT = 2;

class StaticClient {
	static DayTime currentTime;
	static DayTime getCurrentTime();
public:
	static list<Pickup> getNextPickups(const std::initializer_list<ICarrier*> &allowableCarriers, const unsigned int &amountOfPickups = PICKUP_AMOUNT, const unsigned int &delayFromNow = DELAY_PICKUP_TIME);
};


