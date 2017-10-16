#include "stdafx.h"
#include "CppUnitTest.h"
#include "DayTime.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Truck_SchedulesUnitTests
{		
	TEST_CLASS(DayTimeTest)
	{
	public:
		
		TEST_METHOD(OperatorLess_SameObjects_ReturnFalse)
		{
			// Arrange
			DayTime obj1(Days::Monday, 16, 20);
			
			// Act
			bool result = obj1 < obj1;

			// Assert
			Assert::AreEqual(false, result);
		}

	};
}