#include "DateTime.h"

std::string utils::DateTime::getUTC()
{
	time_t now;
	tm tm;
	time(&now);
	gmtime_s(&tm, &now);
	char timeBuffer[sizeof("1970-01-01T00:00:00Z")];
	strftime(timeBuffer, sizeof(timeBuffer), "%FT%TZ", &tm);
	return std::string(timeBuffer);
}
