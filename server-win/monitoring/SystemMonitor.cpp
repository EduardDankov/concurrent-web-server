#include "SystemMonitor.h"

std::shared_ptr<monitoring::SystemMonitor> monitoring::SystemMonitor::getInstance()
{
	static std::shared_ptr<SystemMonitor> instance(new SystemMonitor);
	return instance;
}
