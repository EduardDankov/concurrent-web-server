#pragma once

#ifdef _WIN32
#pragma comment(lib, "Ws2_32.lib")
#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>

#include "../constants.h"

namespace networking
{
	class WinSocket
	{
	protected:
		WSADATA m_wsaData;
		int m_wsaErr;
		WORD m_wVersionRequested;

		SOCKET m_serverSocket{ INVALID_SOCKET };
		sockaddr_in m_serverService;

		void initializeWSA()
		{
			m_wVersionRequested = MAKEWORD(2, 2);
			m_wsaErr = WSAStartup(m_wVersionRequested, &m_wsaData);

			if (m_wsaErr != 0)
			{
				std::cerr << "Failed to initialize WinSock!" << std::endl;
				exit(EXIT_FAILURE);
			}
		}

		void initializeSocket()
		{
			m_serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

			if (m_serverSocket == INVALID_SOCKET)
			{
				std::cerr << "Failed to initialize socket: " << WSAGetLastError() << std::endl;
				WSACleanup();
				exit(EXIT_FAILURE);
			}
		}

		void bindSocket()
		{
			m_serverService.sin_family = AF_INET;
			inet_pton(AF_INET, constants::serverAddr.c_str(), &m_serverService.sin_addr.s_addr);
			m_serverService.sin_port = htons(constants::serverPort);

			if (bind(m_serverSocket, reinterpret_cast<SOCKADDR*>(&m_serverService), sizeof(m_serverService)))
			{
				std::cerr << "Failed to bind socket: " << WSAGetLastError() << std::endl;
				WSACleanup();
				exit(EXIT_FAILURE);
			}
		}

		void listenSocket()
		{
			if (listen(m_serverSocket, constants::backlogSize) == SOCKET_ERROR)
			{
				std::cerr << "Failed to listen socket: " << WSAGetLastError() << std::endl;
				WSACleanup();
				exit(EXIT_FAILURE);
			}
		}

	public:
		WinSocket()
		{
			initializeWSA();
			initializeSocket();
			bindSocket();
			listenSocket();
		}

		void acceptConnection()
		{

		}
	};
}

#endif
