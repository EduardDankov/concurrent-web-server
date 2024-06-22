#include "LinuxSystemMonitor.h"

#include <string>
#include <fstream>
#include <cmath>
#include <vector>
#include <numeric>
#include <sys/types.h>
#include <sys/sysinfo.h>

double monitoring::LinuxSystemMonitor::convertToGB(unsigned long long bytes)
{
	double gigabytes = static_cast<double>(bytes) / std::pow(1024, 3);
	gigabytes = std::round(gigabytes * 100) / 100; // round to 2 digits
	return gigabytes;
}

bool monitoring::LinuxSystemMonitor::getSystemTimes(unsigned long long& idleTime, unsigned long long& totalTime)
{
	std::vector<unsigned long long> times;
	std::ifstream procStat("/proc/stat");
	procStat.ignore(5, ' '); // skip 'cpu' prefix

	unsigned long long value{};
	while (procStat >> value)
	{
		times.push_back(value);
	}

	if (times.size() < 4) return false;
	idleTime = times.at(3);
	totalTime = std::accumulate(times.begin(), times.end(), 0);
}

float monitoring::LinuxSystemMonitor::calculateCpuLoad(unsigned long long idleTicks, unsigned long long totalTicks)
{
	static unsigned long long s_previousTotalTicks = 0;
	static unsigned long long s_previousIdleTicks = 0;

	unsigned long long totalTicksSinceLastTime = totalTicks - s_previousTotalTicks;
	unsigned long long idleTicksSinceLastTime = idleTicks - s_previousIdleTicks;

	float ret = 1.0f - (
		(totalTicksSinceLastTime > 0)
		? (static_cast<float>(idleTicksSinceLastTime)) / totalTicksSinceLastTime
		: 0);

	s_previousTotalTicks = totalTicks;
	s_previousIdleTicks = idleTicks;
	return ret;
}

void monitoring::LinuxSystemMonitor::updateCpuLoad()
{
	unsigned long long idleTime, totalTime;
	while (true)
	{
		m_cpuLoad = getSystemTimes(idleTime, totalTime)
			? calculateCpuLoad(idleTime, totalTime)
			: -1.0f;
		usleep(s_intervalBetweenCpuUpdatesMs * 1000);
	}
}

monitoring::LinuxSystemMonitor::LinuxSystemMonitor() : m_cpuLoad(0), m_cpuUpdateThread([this]() { updateCpuLoad(); }) {}

std::string monitoring::LinuxSystemMonitor::getCpuLoad()
{
	float currentLoad = std::round(m_cpuLoad * 100 * 100) / 100;
	return std::to_string(currentLoad) + '%';
}

std::string monitoring::LinuxSystemMonitor::getMemoryUsage()
{
	struct sysinfo memInfo;
	sysinfo(&memInfo);
	unsigned long long totalMemory = memInfo.totalram * memInfo.mem_unit;
	unsigned long long usedMemory = totalMemory - memInfo.freeram;
	return std::to_string(convertToGB(usedMemory)) + "GB of " + std::to_string(convertToGB(totalMemory)) + "GB";
}
