#pragma once
#include <string>
#include <thread>

#include "FileLogger.h"
#include "../constants.h"

namespace logger
{
	class RequestLogger : public FileLogger
	{
	public:
		RequestLogger() : FileLogger(constants::requestLogPath) {}

		void log(
			const std::thread::id threadId, 
			const std::string functionName, 
			const std::string clientAddr, 
			const std::string request);
	};
}
