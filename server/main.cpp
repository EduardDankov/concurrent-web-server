#include <iostream>
#include <fstream>

#include "constants.h"
#include "logger/FileLogger.h"

int main()
{
	logger::FileLogger::createLogDir(constants::logDirPath);

	logger::FileLogger requestLogger(constants::requestLogPath);
	logger::FileLogger responseLogger(constants::responseLogPath);

	requestLogger.log("Test request");
	responseLogger.log("Test response");

	return 0;
}
