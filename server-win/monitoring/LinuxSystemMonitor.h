#pragma once

#ifdef __linux__
#include <string>
#include <thread>

#include "SystemMonitor.h"

namespace monitoring
{
	class LinuxSystemMonitor : public SystemMonitor
	{
	protected:
		static const time_t s_intervalBetweenCpuUpdatesMs{ 100 };
		float m_cpuLoad;
		std::thread m_cpuUpdateThread;

		double convertToGB(unsigned long long bytes);

		bool getSystemTimes(unsigned long long& idleTime, unsigned long long& totalTime);
		float calculateCpuLoad(unsigned long long idleTicks, unsigned long long totalTicks);
		void updateCpuLoad() override;

		LinuxSystemMonitor();

	public:
		static std::shared_ptr<LinuxSystemMonitor> getInstance();
		
		std::string getCpuLoad() override;
		std::string getMemoryUsage() override;
	};
}

#endif
