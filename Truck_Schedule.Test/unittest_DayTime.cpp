#include "stdafx.h"

TEST(DayTimeTest, CheckComparison)
{
	// Arrange
	DayTime v1(Days::Sunday,15,20);
	DayTime v2(Days::Sunday,16,30);

	// Act
	bool result = v1 < v2;

	// Assert
	ASSERT_EQ(true, result);
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}