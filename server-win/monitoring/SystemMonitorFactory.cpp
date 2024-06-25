#include "SystemMonitorFactory.h"

#if defined _WIN32
#include "WinSystemMonitor.h"
#elif defined __linux__
#include "LinuxSystemMonitor.h"
#endif

std::shared_ptr<monitoring::SystemMonitor> monitoring::SystemMonitorFactory::createSystemMonitor()
{
#if defined _WIN32
	return WinSystemMonitor::getInstance();
#elif defined __linux__
	return LinuxSystemMonitor::getInstance();
#endif
}
