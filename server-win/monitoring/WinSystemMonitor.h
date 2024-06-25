#pragma once
#ifdef _WIN32
#include <string>
#include <thread>
#include <Windows.h>

#include "SystemMonitor.h"

namespace monitoring
{
	class WinSystemMonitor : public SystemMonitor
	{
	protected:
		static const DWORD s_intervalBetweenCpuUpdatesMs{ 100 };
		float m_cpuLoad;
		std::jthread m_cpuUpdateThread;

		double convertToGB(DWORDLONG bytes);

		float calculateCpuLoad(DWORDLONG idleTicks, DWORDLONG totalTicks);
		DWORDLONG fileTimeToInt64(const FILETIME& ft);
		// This function needs to be called at regular intervals to store the load between calls
		void updateCpuLoad() override;

		WinSystemMonitor();

	public:
		static std::shared_ptr<WinSystemMonitor> getInstance();
		
		std::string getCpuLoad() override;
		std::string getMemoryUsage() override;
	};
}

#endif
