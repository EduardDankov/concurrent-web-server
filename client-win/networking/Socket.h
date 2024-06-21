#pragma once

#if defined _WIN32
#include "WinSocket.h"
#elif defined __linux__
#include "LinuxSocket.h"
#endif

namespace networking
{
	class Socket
#if defined _WIN32
		: public WinSocket
#elif defined __linux__
		: public LinuxSocket
#endif
	{};
}
