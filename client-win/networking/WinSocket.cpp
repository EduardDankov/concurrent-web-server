#include "WinSocket.h"

#include <memory>
#include <vector>
#include <string>
#include <iostream>

#include "../../server-win/constants.h"

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
	m_clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (m_clientSocket == INVALID_SOCKET)
	{
		std::cerr << "Failed to initialize socket: " << WSAGetLastError() << std::endl;
		WSACleanup();
		exit(EXIT_FAILURE);
	}
}

void networking::WinSocket::connectSocket()
{
	m_clientAddr.sin_family = AF_INET;
	inet_pton(AF_INET, constants::serverAddr.c_str(), &m_clientAddr.sin_addr.s_addr);
	m_clientAddr.sin_port = htons(constants::serverPort);

	if (connect(m_clientSocket, reinterpret_cast<SOCKADDR*>(&m_clientAddr), sizeof(m_clientAddr)) == SOCKET_ERROR)
	{
		std::cerr << "Failed to connect: " << WSAGetLastError() << std::endl;
		WSACleanup();
		exit(EXIT_FAILURE);
	}
	std::cout << "Connected to " << constants::serverAddr << ":" << constants::serverPort << "..." << std::endl;
}

void networking::WinSocket::handleResponse(SOCKET clientSocket)
{
	std::vector<char> buffer(constants::bufferSize);
	size_t bytesRead = recv(clientSocket, &buffer[0], static_cast<int>(buffer.size()), 0);

	if (bytesRead < 0)
	{
		std::cerr << "Failed to read received data: " << WSAGetLastError() << std::endl;
		return;
	}

	buffer.resize(bytesRead);
	nlohmann::json response = nlohmann::json::parse(buffer.cbegin(), buffer.cend());

	std::cout << "Server response: " << response << '\n' << std::endl;
}

networking::WinSocket::WinSocket()
{
	initializeWSA();
	initializeSocket();
	connectSocket();
}

networking::WinSocket::~WinSocket()
{
	WSACleanup();
}

void networking::WinSocket::sendRequest(const nlohmann::json request)
{
	std::string requestString = request.dump();
	size_t bytesSent = send(m_clientSocket, requestString.c_str(), static_cast<int>(requestString.size()), 0);

	if (bytesSent == SOCKET_ERROR)
	{
		std::cerr << "Failed to send a request: " << WSAGetLastError() << std::endl;
		return;
	}

	handleResponse(m_clientSocket);
}
