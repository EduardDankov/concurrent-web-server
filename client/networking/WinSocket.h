#pragma once

#ifdef _WIN32
#pragma comment(lib, "Ws2_32.lib")
#include <memory>
#include <string>
#include <WinSock2.h>
#include <WS2tcpip.h>

namespace networking
{
	class WinSocket
	{
	protected:
		WSADATA m_wsaData;
		int m_wsaErr;
		WORD m_wVersionRequested;

		SOCKET m_clientSocket{ INVALID_SOCKET };
		sockaddr_in m_clientAddr;
		socklen_t m_clientAddrSize;

		void initializeWSA();
		void initializeSocket();
		void connectSocket();

		void handleResponse(SOCKET clientSocket);

	public:
		WinSocket();

		virtual ~WinSocket();

		void sendRequest(const std::string message);
	};
}

#endif
