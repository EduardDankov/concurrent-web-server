#include "ThreadPool.h"

std::shared_ptr<networking::ThreadPool> networking::ThreadPool::getInstance()
{
	static std::shared_ptr<ThreadPool> instance(new ThreadPool);
	return instance;
}
