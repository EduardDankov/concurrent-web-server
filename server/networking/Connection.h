#pragma once

#if defined _WIN32
#include "WinConnection.h"
#elif defined linux
#include "LinuxConnection.h"
#endif

namespace networking
{
	struct Connection
#if defined _WIN32
		: public WinConnection
#elif defined linux
		: public LinuxConnection
#endif
	{};
}
