#pragma once

#if defined _WIN32
#include "WinSystemMonitor.h"
#elif defined __linux__
#include "LinuxSystemMonitor.h"
#endif

#include <memory>

namespace monitoring
{
	class SystemMonitor
#if defined _WIN32
		: public WinSystemMonitor
#elif defined __linux__
		: public LinuxSystemMonitor
#endif
	{
	public:
		static std::shared_ptr<SystemMonitor> getInstance();
	};
}
