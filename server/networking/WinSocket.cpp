#include "WinSocket.h"

#include <memory>
#include <vector>
#include <string>
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

std::string networking::WinSocket::getClientIP(const sockaddr_in clientAddr)
{
	std::vector<char> addrBuffer(INET_ADDRSTRLEN);
	inet_ntop(AF_INET, &(clientAddr.sin_addr), &addrBuffer[0], INET_ADDRSTRLEN);
	std::string ip;
	addrBuffer.resize(std::distance(addrBuffer.begin(), std::find(addrBuffer.begin(), addrBuffer.end(), 0)));
	ip.append(addrBuffer.cbegin(), addrBuffer.cend());
	return ip;
}

std::string networking::WinSocket::generateResponse(const std::string request)
{
	if (request == "getserverversion")
	{
		return constants::serverVersion;
	}
	if (request == "getserverstatus")
	{
		return "CPU, RAM";
	}

	return "Bad Request";
}

void networking::WinSocket::handleConnection(SOCKET clientSocket)
{
	std::vector<char> buffer(constants::bufferSize);
	size_t bytesRead = recv(clientSocket, &buffer[0], static_cast<int>(buffer.size()), 0);

	if (bytesRead < 0)
	{
		std::cerr << "Failed to read received data: " << WSAGetLastError() << std::endl;
		return;
	}

	std::string request;
	buffer.resize(bytesRead);
	request.append(buffer.cbegin(), buffer.cend());

	global::requestLogger.log(
		std::this_thread::get_id(), 
		"networking::WinSocket::handleConnection", 
		getClientIP(m_clientAddr),
		request
	);

	std::string response = generateResponse(request);
	size_t bytesSent = send(clientSocket, response.c_str(), response.size(), 0);

	if (bytesSent < 0)
	{
		std::cerr << "Failed to send response: " << WSAGetLastError() << std::endl;
		return;
	}

	global::responseLogger.log(
		std::this_thread::get_id(),
		"networking::WinSocket::handleConnection",
		getClientIP(m_clientAddr),
		response
	);
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
