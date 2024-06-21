#include "LinuxSystemMonitor.h"

#include <string>
#include <cmath>

double monitoring::LinuxSystemMonitor::convertToGB(unsigned long long bytes)
{
	double gigabytes = static_cast<double>(bytes) / std::pow(1024, 3);
	gigabytes = std::round(gigabytes * 100) / 100; // round to 2 digits
	return gigabytes;
}

monitoring::LinuxSystemMonitor::LinuxSystemMonitor() {}

std::string monitoring::LinuxSystemMonitor::getCpuLoad()
{
	return "-1%";
}

std::string monitoring::LinuxSystemMonitor::getMemoryUsage()
{
	struct sysinfo memInfo;
	sysinfo(&memInfo);
	unsigned long long totalMemory = memInfo.totalram * memInfo.mem_unit;
	unsigned long long usedMemory = totalMemory - memInfo.freeram;
	return std::to_string(convertToGB(usedMemory)) + "GB of " + std::to_string(convertToGB(totalMemory)) + "GB";
}
