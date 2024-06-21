#include "WinSocket.h"

#include <memory>
#include <format>
#include <vector>
#include <string>
#include <iostream>

#include "Connection.h"
#include "ThreadPool.h"
#include "../logger/RequestLogger.h"
#include "../logger/ResponseLogger.h"
#include "../monitoring/SystemMonitor.h"

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

std::string networking::WinSocket::getClientIP(std::shared_ptr<Connection> connection)
{
	std::vector<char> addrBuffer(INET_ADDRSTRLEN);
	inet_ntop(AF_INET, &(connection->clientAddr.sin_addr), &addrBuffer[0], INET_ADDRSTRLEN);
	std::string ip;
	addrBuffer.resize(std::distance(addrBuffer.begin(), std::find(addrBuffer.begin(), addrBuffer.end(), 0)));
	ip.append(addrBuffer.cbegin(), addrBuffer.cend());
	return ip;
}

nlohmann::json networking::WinSocket::generateResponse(const nlohmann::json request)
{
	if (request.contains("message"))
	{
		if (request.at("message") == "getserverversion")
		{
			return {
				{"version", constants::serverVersion}
			};
		}
		if (request.at("message") == "getserverstatus")
		{
			std::string cpuUsage = monitoring::SystemMonitor::getInstance()->getCpuLoad();
			std::string memoryUsage = monitoring::SystemMonitor::getInstance()->getMemoryUsage();
			return {
				{"cpuUsage", cpuUsage},
				{"memoryUsage", memoryUsage}
			};
		}
	}

	return {
		{"error", "Bad Request"}
	};
}

void networking::WinSocket::handleConnection(std::shared_ptr<Connection> connection)
{
	std::vector<char> buffer(constants::bufferSize);
	size_t bytesRead = recv(connection->clientSocket, &buffer[0], static_cast<int>(buffer.size()), 0);

	if (bytesRead < 0)
	{
		std::cerr << "Failed to read received data: " << WSAGetLastError() << std::endl;
		return;
	}

	buffer.resize(bytesRead);
	nlohmann::json request = nlohmann::json::parse(buffer.cbegin(), buffer.cend());

	logger::RequestLogger::getInstance()->log(
		std::this_thread::get_id(), 
		"networking::WinSocket::handleConnection", 
		getClientIP(connection),
		request
	);

	std::string responseString = generateResponse(request).dump();
	size_t bytesSent = send(connection->clientSocket, responseString.c_str(), static_cast<int>(responseString.size()), 0);

	if (bytesSent < 0)
	{
		std::cerr << "Failed to send response: " << WSAGetLastError() << std::endl;
		return;
	}

	logger::ResponseLogger::getInstance()->log(
		std::this_thread::get_id(),
		"networking::WinSocket::handleConnection",
		getClientIP(connection),
		responseString
	);
}

networking::WinSocket::WinSocket()
{
	initializeWSA();
	initializeSocket();
	bindSocket();
	listenSocket();
}

networking::WinSocket::~WinSocket()
{
	WSACleanup();
}

void networking::WinSocket::acceptConnection()
{
	std::shared_ptr<Connection> connection = std::make_shared<Connection>();

	connection->clientAddrSize = sizeof(sockaddr_in);
	connection->clientSocket = accept(
		m_serverSocket, 
		reinterpret_cast<SOCKADDR*>(&connection->clientAddr), 
		&connection->clientAddrSize);

	if (connection->clientSocket == INVALID_SOCKET)
	{
		std::cerr << "Failed to accept connection: " << WSAGetLastError() << std::endl;
		return;
	}

	networking::ThreadPool::getInstance()->queueConnection(connection);
}
