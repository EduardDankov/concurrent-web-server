#include <iostream>
#include <fstream>
#include <memory>

#include "constants.h"

#include "logger/FileLogger.h"
#include "networking/Socket.h"

int main()
{
	logger::FileLogger::createLogDir(constants::logDirPath);

	networking::Socket socket{};
	while (true)
	{
		socket.acceptConnection();
	}
	return 0;
}
