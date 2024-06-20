#include "ResponseLogger.h"

#include "../utils/DateTime.h"

void logger::ResponseLogger::log(
	const std::thread::id threadId,
	const std::string functionName,
	const std::string clientAddr,
	const std::string response)
{
	*m_os << "Thread #" << threadId << " - "
		<< utils::DateTime::getUTC() << " - "
		<< "[" << functionName << "] - "
		<< "response to " << clientAddr << " - "
		<< response << '\n';
}
