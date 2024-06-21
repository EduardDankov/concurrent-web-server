#pragma once

#ifdef __linux__
#include <memory>
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "../utils/Json.h"

namespace networking
{
	class LinuxSocket
	{
	protected:
		int m_clientSocket{ -1 };
		sockaddr_in m_clientAddr;
		socklen_t m_clientAddrSize;

		void initializeSocket();
		void connectSocket();

		void handleResponse(int clientSocket);

	public:
		LinuxSocket();

		virtual ~LinuxSocket();

		void sendRequest(const nlohmann::json request);
	};
}

#endif
