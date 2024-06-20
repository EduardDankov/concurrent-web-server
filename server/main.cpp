#include <iostream>
#include <fstream>

#include "constants.h"
#include "logger/FileLogger.h"
#include "networking/Socket.h"

int main()
{
	logger::FileLogger::createLogDir(constants::logDirPath);

	logger::FileLogger requestLogger(constants::requestLogPath);
	logger::FileLogger responseLogger(constants::responseLogPath);

	requestLogger.log("Test request");
	responseLogger.log("Test response");

	networking::Socket socket{};
	while (true)
	{
		socket.acceptConnection();
	}
	return 0;
}
