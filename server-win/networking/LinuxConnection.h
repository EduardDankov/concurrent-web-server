#pragma once

#ifdef __linux__
#include <sys/socket.h>
#include <arpa/inet.h>

namespace networking
{
	struct LinuxConnection
	{
		int clientSocket{ -1 };
		sockaddr_in clientAddr{};
		socklen_t clientAddrSize{};
	};
}

#endif
