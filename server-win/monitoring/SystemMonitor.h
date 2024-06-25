#pragma once
#include <memory>
#include <string>

namespace monitoring
{
	class SystemMonitor
	{
	protected:
		virtual void updateCpuLoad() = 0;

	public:
		virtual std::string getCpuLoad() = 0;
		virtual std::string getMemoryUsage() = 0;
	};
}
