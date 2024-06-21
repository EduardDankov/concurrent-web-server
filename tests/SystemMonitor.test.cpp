#include "pch.h"

#include <regex>
#include <vector>
#include <string>

#include "../server-win/monitoring/SystemMonitor.cpp"
#if defined _WIN32
#include "../server-win/monitoring/WinSystemMonitor.cpp"
#elif defined __linux__
#include "../server-win/monitoring/LinuxSystemMonitor.cpp"
#endif


TEST(SystemMonitor, isCpuLoadValid)
{
	std::string cpuLoadString = monitoring::SystemMonitor::getInstance()->getCpuLoad();
	std::regex pattern(R"([+-]?\d+(\.\d+)*)"); // matches signed numbers with optional floating point
	std::smatch match;

	std::vector<double> values;
	std::string searchString = cpuLoadString;
	while (std::regex_search(searchString, match, pattern))
	{
		values.push_back(std::stod(match.str()));
		searchString = std::string(
			cpuLoadString.begin() + cpuLoadString.find(match[0]) + match[0].str().size(),
			cpuLoadString.end());
	}

	EXPECT_EQ(values.size(), 1); // cpuLoadString contains one value: CPU load in %
	EXPECT_GE(values.at(0), 0); // CPU load is greater or equal to 0%
	EXPECT_LE(values.at(0), 100); // CPU load is lower or equal to 100%
}

TEST(SystemMonitor, isMemoryUsageValid)
{
	std::string memoryUsageString = monitoring::SystemMonitor::getInstance()->getMemoryUsage();
	std::regex pattern(R"([+-]?\d+\.\d+)"); // matches signed numbers with floating point
	std::smatch match;

	std::vector<double> values;
	std::string searchString = memoryUsageString;
	while (std::regex_search(searchString, match, pattern))
	{
		values.push_back(std::stod(match.str()));
		searchString = std::string(
			memoryUsageString.begin() + memoryUsageString.find(match[0]) + match[0].str().size(), 
			memoryUsageString.end());
	}

	EXPECT_EQ(values.size(), 2); // memoryUsageString contains two values: usage and total
	EXPECT_GE(values.at(0), 0); // used memory is greater or equal to zero
	EXPECT_GT(values.at(1), 0); // total memory is greater than zero
	EXPECT_LE(values.at(0), values.at(1)); // used memory is less or equal to total memory
}
