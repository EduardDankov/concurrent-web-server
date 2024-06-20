#pragma once

#ifdef _WIN32
#pragma comment(lib, "Ws2_32.lib")
#include <memory>
#include <WinSock2.h>
#include <WS2tcpip.h>

#include "../logger/RequestLogger.h"

namespace networking
{
	class WinSocket
	{
	protected:
		WSADATA m_wsaData;
		int m_wsaErr;
		WORD m_wVersionRequested;

		SOCKET m_serverSocket{ INVALID_SOCKET };
		SOCKET m_clientSocket{ INVALID_SOCKET };
		sockaddr_in m_serverAddr;
		sockaddr_in m_clientAddr;
		socklen_t m_clientAddrSize;

		void initializeWSA();
		void initializeSocket();
		void bindSocket();
		void listenSocket();

		void handleConnection(SOCKET clientSocket);

	public:
		WinSocket();

		void acceptConnection();
	};
}

#endif
