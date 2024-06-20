#include <iostream>
#include "networking/Socket.h"
#include "cli/RequestSelector.h"

int main()
{
	networking::Socket socket{};
	while (true)
	{
		socket.sendRequest(cli::RequestSelector::select());
		std::cin.get();
	}
	return 0;
}
