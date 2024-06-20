#pragma once
#include <string>
#include <thread>
#include <memory>

#include "FileLogger.h"
#include "../constants.h"

namespace logger
{
	class RequestLogger : public FileLogger
	{
	private:
		RequestLogger() : FileLogger(constants::requestLogPath) {}

	public:
		static std::shared_ptr<RequestLogger> getInstance();

		void log(
			const std::thread::id threadId, 
			const std::string functionName, 
			const std::string clientAddr, 
			const std::string request);
	};
}
