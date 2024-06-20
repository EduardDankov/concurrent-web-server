#pragma once

#if defined _WIN32
#include "WinSocket.h"
#elif defined linux
#include "LinuxSocket.h"
#endif

namespace networking
{
	class Socket
#if defined _WIN32
		: public WinSocket
#elif defined linux
		: public LinuxSocket
#endif
	{};
}
