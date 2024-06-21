#include "ThreadPool.h"

networking::ThreadPool::ThreadPool()
{
	for (auto& thread : m_threads)
	{
		thread = std::thread([this]() { checkForConnections(); } );
	}
}

std::shared_ptr<networking::ThreadPool> networking::ThreadPool::getInstance()
{
	static std::shared_ptr<ThreadPool> instance(new ThreadPool);
	return instance;
}

void networking::ThreadPool::checkForConnections()
{
	while (true)
	{
		std::unique_lock<std::mutex> lock(m_queueMutex);
		m_queueCondition.wait(lock, [this]() { return !m_requestQueue.empty(); });
		std::shared_ptr<Connection> connection = m_requestQueue.front();
		m_requestQueue.pop();
		m_queueCondition.notify_one();
		networking::Socket::getInstance()->handleConnection(connection);
	}
}

void networking::ThreadPool::queueConnection(std::shared_ptr<Connection> connection)
{
	std::unique_lock<std::mutex> lock(m_queueMutex);
	m_requestQueue.push(connection);
	m_queueCondition.notify_one();
}
