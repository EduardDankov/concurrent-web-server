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

		ThreadPool();

	public:
		static std::shared_ptr<ThreadPool> getInstance();
		void checkForConnections();
		void queueConnection(std::shared_ptr<Connection> connection);
	};
}
