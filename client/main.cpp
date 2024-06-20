#include <iostream>
#include "networking/Socket.h"

int main()
{
	networking::Socket socket{};
	while (true)
	{
		socket.sendRequest("getserverversion");
		std::cin.get();
	}
	return 0;
}
