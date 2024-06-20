#include <iostream>
#include "networking/Socket.h"
#include "cli/RequestSelector.h"

int main()
{
	while (true)
	{
		networking::Socket socket{};
		std::string request = cli::RequestSelector::select();
		socket.sendRequest(request);
		std::cin.get();
	}
	return 0;
}
