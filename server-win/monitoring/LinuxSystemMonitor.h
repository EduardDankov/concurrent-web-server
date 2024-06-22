#pragma once

#ifdef __linux__
#include <string>
#include <thread>

namespace monitoring
{
	class LinuxSystemMonitor
	{
	protected:
		static const time_t s_intervalBetweenCpuUpdatesMs{ 100 };
		float m_cpuLoad;
		std::thread m_cpuUpdateThread;

		double convertToGB(unsigned long long bytes);

		bool getSystemTimes(unsigned long long& idleTime, unsigned long long& totalTime);
		float calculateCpuLoad(unsigned long long idleTicks, unsigned long long totalTicks);
		void updateCpuLoad();

	public:
		LinuxSystemMonitor();
		
		std::string getCpuLoad();
		std::string getMemoryUsage();
	};
}

#endif
