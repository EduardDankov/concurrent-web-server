#include "constants.h"

#include "logger/FileLogger.h"
#include "networking/Socket.h"
#include "monitoring/SystemMonitorFactory.h"

int main()
{
	// SystemMonitor instance has to be created before first connection for correct CPU usage measurement
	monitoring::SystemMonitorFactory::createSystemMonitor();
	logger::FileLogger::createLogDir(constants::logDirPath);

	while (true)
	{
		networking::Socket::getInstance()->acceptConnection();
	}
	return 0;
}
