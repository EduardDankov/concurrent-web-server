#pragma once

#if defined _WIN32
#include "WinConnection.h"
#elif defined __linux__
#include "LinuxConnection.h"
#endif

namespace networking
{
	struct Connection
#if defined _WIN32
		: public WinConnection
#elif defined __linux__
		: public LinuxConnection
#endif
	{};
}
