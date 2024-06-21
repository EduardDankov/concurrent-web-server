#pragma once

#ifdef __linux__
#include <string>
#include <sys/types.h>
#include <sys/sysinfo.h>

namespace monitoring
{
	class LinuxSystemMonitor
	{
	protected:
		double convertToGB(unsigned long long bytes);

	public:
		LinuxSystemMonitor();
		
		std::string getCpuLoad();
		std::string getMemoryUsage();
	};
}

#endif
