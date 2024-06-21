#include "WinSystemMonitor.h"

#include <format>
#include <string>
#include <Windows.h>
#include <tchar.h>
#include <pdh.h>

double monitoring::WinSystemMonitor::convertToGB(DWORDLONG bytes)
{
	double gigabytes = static_cast<double>(bytes) / std::pow(1024, 3);
	gigabytes = std::round(gigabytes * 100) / 100; // round to 2 digits
	return gigabytes;
}

float monitoring::WinSystemMonitor::calculateCpuLoad(DWORDLONG idleTicks, DWORDLONG totalTicks)
{
	static DWORDLONG s_previousTotalTicks = 0;
	static DWORDLONG s_previousIdleTicks = 0;

	DWORDLONG totalTicksSinceLastTime = totalTicks - s_previousTotalTicks;
	DWORDLONG idleTicksSinceLastTime = idleTicks - s_previousIdleTicks;

	float ret = 1.0f - (
		(totalTicksSinceLastTime > 0) 
		? (static_cast<float>(idleTicksSinceLastTime)) / totalTicksSinceLastTime 
		: 0);

	s_previousTotalTicks = totalTicks;
	s_previousIdleTicks = idleTicks;
	return ret;
}

DWORDLONG monitoring::WinSystemMonitor::fileTimeToInt64(const FILETIME& ft)
{
	return ((static_cast<DWORDLONG>(ft.dwHighDateTime)) << 32) | (static_cast<DWORDLONG>(ft.dwLowDateTime));
}

void monitoring::WinSystemMonitor::updateCpuLoad()
{
	FILETIME idleTime, kernelTime, userTime;
	m_cpuLoad = GetSystemTimes(&idleTime, &kernelTime, &userTime)
		? calculateCpuLoad(fileTimeToInt64(idleTime), fileTimeToInt64(kernelTime) + fileTimeToInt64(userTime))
		: -1.0f;
	Sleep(s_intervalBetweenCpuUpdatesMs);
}

monitoring::WinSystemMonitor::WinSystemMonitor() : m_cpuLoad(0), m_cpuUpdateThread([this]() { updateCpuLoad(); }) {}

std::string monitoring::WinSystemMonitor::getCpuLoad()
{
	float currentLoad = std::round(m_cpuLoad * 100 * 100) / 100;
	return std::format("{}%", currentLoad);
}

std::string monitoring::WinSystemMonitor::getMemoryUsage()
{
	MEMORYSTATUSEX memInfo;
	memInfo.dwLength = sizeof(MEMORYSTATUSEX);
	GlobalMemoryStatusEx(&memInfo);
	DWORDLONG totalMemory = memInfo.ullTotalPhys;
	DWORDLONG usedMemory = totalMemory - memInfo.ullAvailPhys;
	return std::format("{}GB of {}GB", convertToGB(usedMemory), convertToGB(totalMemory));
}
