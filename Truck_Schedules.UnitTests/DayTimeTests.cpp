#include "stdafx.h"
#include "CppUnitTest.h"
#include "DayTime.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TruckSchedules_UnitTests_DayTime
{		
	TEST_CLASS(DayTime_Test)
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

		TEST_METHOD(OperatorLess_DifObjects_ReturnTrue)
		{
			// Arrange
			DayTime obj1(Days::Monday, 16, 20);
			DayTime obj2(Days::Monday, 20, 20);

			// Act
			bool result = obj1 < obj2;

			// Assert
			Assert::AreEqual(true, result);
		}

		TEST_METHOD(OperatorEqual_SameObjects_ReturnTrue)
		{
			// Arrange
			DayTime obj1(Days::Monday, 16, 20);

			// Act
			bool result = obj1 == obj1;

			// Assert
			Assert::AreEqual(true, result);
		}

		TEST_METHOD(OperatorEqual_DifObjects_ReturnFalse)
		{
			// Arrange
			DayTime obj1(Days::Monday, 16, 20);
			DayTime obj2(Days::Sunday, 19, 10);

			// Act
			bool result = obj1 == obj2;

			// Assert
			Assert::AreEqual(false, result);
		}

		TEST_METHOD(OperatorPlus_DayTimePlusInt_ReturnTrue)
		{
			// Arrange
			DayTime obj1(Days::Monday, 10, 20);
			int hours{ 10 };
			DayTime obj2(Days::Monday, 20, 20);

			// Act
			bool result = ((obj1 + hours) == obj2);

			// Assert
			Assert::AreEqual(true, result);
		}

		TEST_METHOD(ToString_ReturnString)
		{
			// Arrange
			DayTime obj1(Days::Monday, 10, 20);

			// Act
			string result = obj1.toString();
			string example = "Monday, 10:20";
			// Assert
			Assert::AreEqual(example, result);
		}

		TEST_METHOD(ToString_EmptyObject_ReturnSundayMidnight)
		{
			// Arrange
			DayTime obj1;

			// Act
			string result = obj1.toString();
			string example = "Sunday, 0:0";
			// Assert
			Assert::AreEqual(example, result);
		}
	};
}