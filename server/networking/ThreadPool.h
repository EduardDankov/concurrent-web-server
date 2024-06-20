#pragma once
#include <array>
#include <queue>
#include <thread>
#include <memory>

#include "Socket.h"
#include "Connection.h"
#include "../constants.h"

namespace networking
{
	class ThreadPool
	{
	private:
		std::array<std::thread, constants::threadPoolSize> m_threads{};
		std::queue<std::shared_ptr<Connection>> requestQueue{};

		ThreadPool()
		{
			for (auto& thread : m_threads)
			{
				thread = std::thread([this]() { checkForConnections(); });
			}
		}

	public:
		static std::shared_ptr<ThreadPool> getInstance();

		void checkForConnections()
		{
			if (!requestQueue.empty())
			{
				std::shared_ptr<Connection> connection = requestQueue.front();
				requestQueue.pop();
				networking::Socket::getInstance()->handleConnection(connection);
			}
		}

		void queueConnection(std::shared_ptr<Connection> connection)
		{
			requestQueue.push(connection);
		}
	};
}
