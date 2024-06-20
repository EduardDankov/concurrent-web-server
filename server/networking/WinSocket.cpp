#include "WinSocket.h"

#include <memory>
#include <iostream>

#include "../global.h"

void networking::WinSocket::initializeWSA()
{
	m_wVersionRequested = MAKEWORD(2, 2);
	m_wsaErr = WSAStartup(m_wVersionRequested, &m_wsaData);

	if (m_wsaErr != 0)
	{
		std::cerr << "Failed to initialize WinSock!" << std::endl;
		exit(EXIT_FAILURE);
	}
}

void networking::WinSocket::initializeSocket()
{
	m_serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (m_serverSocket == INVALID_SOCKET)
	{
		std::cerr << "Failed to initialize socket: " << WSAGetLastError() << std::endl;
		WSACleanup();
		exit(EXIT_FAILURE);
	}
}

void networking::WinSocket::bindSocket()
{
	m_serverAddr.sin_family = AF_INET;
	inet_pton(AF_INET, constants::serverAddr.c_str(), &m_serverAddr.sin_addr.s_addr);
	m_serverAddr.sin_port = htons(constants::serverPort);

	if (bind(m_serverSocket, reinterpret_cast<SOCKADDR*>(&m_serverAddr), sizeof(m_serverAddr)))
	{
		std::cerr << "Failed to bind socket: " << WSAGetLastError() << std::endl;
		WSACleanup();
		exit(EXIT_FAILURE);
	}
}

void networking::WinSocket::listenSocket()
{
	if (listen(m_serverSocket, constants::backlogSize) == SOCKET_ERROR)
	{
		std::cerr << "Failed to listen socket: " << WSAGetLastError() << std::endl;
		WSACleanup();
		exit(EXIT_FAILURE);
	}
	std::cout << "Listening to " << constants::serverAddr << ":" << constants::serverPort << "..." << std::endl;
}

void networking::WinSocket::handleConnection(SOCKET clientSocket)
{
	char buffer[constants::bufferSize];
	size_t bytesRead = recv(clientSocket, buffer, constants::bufferSize, 0);

	if (bytesRead < 0)
	{
		std::cerr << "Failed to read received data: " << WSAGetLastError() << std::endl;
		return;
	}

	global::requestLogger.log(std::this_thread::get_id(), "networking::WinSocket::handleConnection", buffer);
}

networking::WinSocket::WinSocket()
{
	initializeWSA();
	initializeSocket();
	bindSocket();
	listenSocket();
}

void networking::WinSocket::acceptConnection()
{
	m_clientAddrSize = sizeof(sockaddr_in);
	m_clientSocket = accept(m_serverSocket, reinterpret_cast<SOCKADDR*>(&m_clientAddr), &m_clientAddrSize);

	if (m_clientSocket == INVALID_SOCKET)
	{
		std::cerr << "Failed to accept connection: " << WSAGetLastError() << std::endl;
		WSACleanup();
		return;
	}

	handleConnection(m_clientSocket);
}
