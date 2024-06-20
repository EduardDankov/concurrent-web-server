#include "RequestLogger.h"

#include "../utils/DateTime.h"

void logger::RequestLogger::log(const std::thread::id threadId, const std::string functionName, const char* request)
{
	*m_os << "Thread #" << threadId << " - "
		  << utils::DateTime::getUTC() << " - " 
		  << "[" << functionName << "] - "
		  << "request from ..." << " - " 
		  << request << '\n';
}