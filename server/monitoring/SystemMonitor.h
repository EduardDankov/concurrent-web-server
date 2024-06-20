#pragma once

#if defined _WIN32
#include "WinSystemMonitor.h"
#elif defined linux
#include "LinuxSystemMonitor.h"
#endif

#include <memory>

namespace monitoring
{
	class SystemMonitor
#if defined _WIN32
		: public WinSystemMonitor
#elif defined linux
		: public LinuxSystemMonitor
#endif
	{
	public:
		static std::shared_ptr<SystemMonitor> getInstance();
	};
}
