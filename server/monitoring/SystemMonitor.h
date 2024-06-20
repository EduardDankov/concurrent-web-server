#pragma once

#if defined _WIN32
#include "WinSystemMonitor.h"
#elif defined linux
#include "LinuxSystemMonitor.h"
#endif

namespace monitoring
{
	class SystemMonitor
#if defined _WIN32
		: public WinSystemMonitor
#elif defined linux
		: public LinuxSystemMonitor
#endif
	{};
}
