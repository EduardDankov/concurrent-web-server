#include "DateTime.h"

std::string utils::DateTime::getUTC()
{
	time_t now;
	tm tm;
	time(&now);
#if defined _WIN32
	gmtime_s(&tm, &now);
#elif defined __linux__
	gmtime_r(&now, &tm);
#endif
	char timeBuffer[sizeof("1970-01-01T00:00:00Z")];
	strftime(timeBuffer, sizeof(timeBuffer), "%FT%TZ", &tm);
	return std::string(timeBuffer);
}
