#include "LinuxSocket.h"
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "../../server-win/constants.h"

void networking::LinuxSocket::initializeSocket()
{
	m_clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (m_clientSocket == -1)
	{
		std::cerr << "Failed to initialize socket." << std::endl;
		exit(EXIT_FAILURE);
	}
}

void networking::LinuxSocket::connectSocket()
{
	m_clientAddr.sin_family = AF_INET;
	inet_pton(AF_INET, constants::serverAddr.c_str(), &m_clientAddr.sin_addr.s_addr);
	m_clientAddr.sin_port = htons(constants::serverPort);

	if (connect(m_clientSocket, reinterpret_cast<sockaddr*>(&m_clientAddr), sizeof(m_clientAddr)) == -1)
	{
		std::cerr << "Failed to connect. " << std::endl;
		exit(EXIT_FAILURE);
	}
	std::cout << "Connected to " << constants::serverAddr << ":" << constants::serverPort << "..." << std::endl;
}

void networking::LinuxSocket::handleResponse(int clientSocket)
{
	std::vector<char> buffer(constants::bufferSize);
	size_t bytesRead = recv(clientSocket, &buffer[0], static_cast<int>(buffer.size()), 0);

	if (bytesRead < 0)
	{
		std::cerr << "Failed to read received data. " << std::endl;
		return;
	}

	buffer.resize(bytesRead);
	nlohmann::json response = nlohmann::json::parse(buffer.cbegin(), buffer.cend());

	std::cout << "Server response: " << response << '\n' << std::endl;
}

networking::LinuxSocket::LinuxSocket()
{
	initializeSocket();
	connectSocket();
}

networking::LinuxSocket::~LinuxSocket() {}

void networking::LinuxSocket::sendRequest(const nlohmann::json request)
{
	std::string requestString = request.dump();
	ssize_t bytesSent = send(m_clientSocket, requestString.c_str(), static_cast<int>(requestString.size()), 0);

	if (bytesSent == -1)
	{
		std::cerr << "Failed to send a request. " << std::endl;
		return;
	}

	handleResponse(m_clientSocket);
}
