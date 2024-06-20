#pragma once

#ifdef _WIN32
#pragma comment(lib, "Ws2_32.lib")
#include <WinSock2.h>
#include <WS2tcpip.h>

namespace networking
{
	struct WinConnection
	{
		SOCKET clientSocket{ INVALID_SOCKET };
		sockaddr_in clientAddr{};
		socklen_t clientAddrSize{};
	};
}

#endif
