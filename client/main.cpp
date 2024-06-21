#include <iostream>
#include "networking/Socket.h"
#include "cli/RequestSelector.h"
#include "utils/Json.h"

int main()
{
	while (true)
	{
		networking::Socket socket{};
		nlohmann::json request = cli::RequestSelector::select();
		socket.sendRequest(request);
		std::cin.get();
	}
	return 0;
}
