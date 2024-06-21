#include "Socket.h"

std::shared_ptr<networking::Socket> networking::Socket::getInstance()
{
	static std::shared_ptr<Socket> instance(new Socket);
	return instance;
}
