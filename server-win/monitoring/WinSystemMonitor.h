#pragma once

#ifdef _WIN32
#include <string>
#include <thread>
#include <Windows.h>

namespace monitoring
{
	class WinSystemMonitor
	{
	protected:
		static const DWORD s_intervalBetweenCpuUpdatesMs{ 100 };
		float m_cpuLoad;
		std::jthread m_cpuUpdateThread;

		double convertToGB(DWORDLONG bytes);

		float calculateCpuLoad(DWORDLONG idleTicks, DWORDLONG totalTicks);
		DWORDLONG fileTimeToInt64(const FILETIME& ft);
		// This function needs to be called at regular intervals to store the load between calls
		void updateCpuLoad();

	public:
		WinSystemMonitor();
		
		std::string getCpuLoad();
		std::string getMemoryUsage();
	};
}

#endif
