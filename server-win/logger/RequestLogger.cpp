#include "RequestLogger.h"

#include "../utils/DateTime.h"

std::shared_ptr<logger::RequestLogger> logger::RequestLogger::getInstance()
{
	static std::shared_ptr<RequestLogger> instance(new RequestLogger);
	return instance;
}

void logger::RequestLogger::log(
	const std::thread::id threadId, 
	const std::string functionName, 
	const std::string clientAddr,
	const nlohmann::json request)
{
	std::stringstream ss;
	ss << "Thread #" << threadId << " - "
	   << utils::DateTime::getUTC() << " - " 
	   << "[" << functionName << "] - "
	   << "request from " << clientAddr << " - " 
	   << request.dump();
	FileLogger::log(ss.str());
}
