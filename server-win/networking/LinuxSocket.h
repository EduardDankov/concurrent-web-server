#pragma once

#ifdef __linux__
#include <memory>
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "Connection.h"
#include "../utils/Json.h"

namespace networking
{
	class LinuxSocket
	{
	protected:
		int m_serverSocket{ -1 };
		sockaddr_in m_serverAddr;

		void initializeSocket();
		void bindSocket();
		void listenSocket();

		std::string getClientIP(std::shared_ptr<Connection> connection);
		nlohmann::json generateResponse(const nlohmann::json request);

	public:
		LinuxSocket();
		virtual ~LinuxSocket();

		void acceptConnection();
		void handleConnection(std::shared_ptr<Connection> connection);
	};
}

#endif
