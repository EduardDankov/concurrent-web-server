#pragma once
#include <array>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
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
		std::queue<std::shared_ptr<Connection>> m_requestQueue{};

		std::mutex m_queueMutex;
		std::condition_variable m_queueCondition;

		ThreadPool();

	public:
		static std::shared_ptr<ThreadPool> getInstance();
		void checkForConnections();
		void queueConnection(std::shared_ptr<Connection> connection);
	};
}
