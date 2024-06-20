#pragma once
#include <string>
#include <thread>

#include "FileLogger.h"
#include "../constants.h"

namespace logger
{
	class ResponseLogger : public FileLogger
	{
	public:
		ResponseLogger() : FileLogger(constants::responseLogPath) {}

		void log(
			const std::thread::id threadId,
			const std::string functionName,
			const std::string clientAddr,
			const std::string response);
	};
}
