#include "ThreadPool.h"

networking::ThreadPool::ThreadPool()
{
	for (auto& thread : m_threads)
	{
		thread = std::thread([this]() { checkForConnections(); });
	}
}

std::shared_ptr<networking::ThreadPool> networking::ThreadPool::getInstance()
{
	static std::shared_ptr<ThreadPool> instance(new ThreadPool);
	return instance;
}

void networking::ThreadPool::checkForConnections()
{
	if (!m_requestQueue.empty())
	{
		std::shared_ptr<Connection> connection = m_requestQueue.front();
		m_requestQueue.pop();
		networking::Socket::getInstance()->handleConnection(connection);
	}
}

void networking::ThreadPool::queueConnection(std::shared_ptr<Connection> connection)
{
	m_requestQueue.push(connection);
}
