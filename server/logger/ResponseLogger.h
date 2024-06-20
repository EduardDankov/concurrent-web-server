#pragma once
#include <string>
#include <thread>
#include <memory>

#include "FileLogger.h"
#include "../constants.h"

namespace logger
{
	class ResponseLogger : public FileLogger
	{
	private:
		ResponseLogger() : FileLogger(constants::responseLogPath) {}
	
	public:
		static std::shared_ptr<ResponseLogger> getInstance();

		void log(
			const std::thread::id threadId,
			const std::string functionName,
			const std::string clientAddr,
			const std::string response);
	};
}
