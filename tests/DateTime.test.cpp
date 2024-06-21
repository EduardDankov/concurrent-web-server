#include "pch.h"

#include <string>

#include "../server-win/utils/DateTime.cpp"

TEST(DateTime, isLengthCorrect)
{
	std::string dateString = utils::DateTime::getUTC();
	size_t expectedLength = sizeof("1970-01-01T00:00:00Z") - 1; // exclude null terminator
	EXPECT_EQ(dateString.size(), expectedLength); // length of dateString is equal to standard length
}

TEST(DateTime, isYearCorrect)
{
	std::string dateString = utils::DateTime::getUTC();
	EXPECT_NE(dateString.find("2024"), std::string::npos); // substring with current year exists in dateString
}
