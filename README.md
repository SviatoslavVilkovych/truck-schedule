# truck-schedule
One of projects that i am doing for the improving my skill.

Current problems of my code that I should fix:
- Files are not structured
- Project can't be built with Make - only with Visual Studio (not supported with Visual Studio for Mac, so I couldn't run it at all)
- Can't understand how it can work potentially - main is empty, no global objects are created (there are only class definitions).
- Source is hard to read
- There are no comments at all
- All business logic is located in one function - list<Pickup> StaticClient::getNextPickups(const std::initializer_list<ICarrier*> &allowableCarriers, const unsigned int &amountOfPickups, const unsigned int &delayFromNow)
  - It is hard to understand logic because there are 3 nested for loops wrapped with try-catch block (can't understand what is the reason for try-catch)
- Some excessive constructions and approaches are used.
