#include "RequestSelector.h"

#include <iostream>
#include <vector>

nlohmann::json cli::RequestSelector::select()
{
	std::vector<std::string> validRequests{ "getserverversion", "getserverstatus" };

	while (true)
	{
		std::cout << "Please enter request ID:" << '\n';
		for (size_t i = 0; i < validRequests.size(); i++)
		{
			std::cout << i << " - " << validRequests.at(i) << '\n';
		}
		std::cout << std::endl;

		size_t requestId{};
		if (!(std::cin >> requestId) || requestId < 0 || requestId >= validRequests.size())
		{
			std::cout << "The entered value is not a valid request ID." << std::endl;
			continue;
		}
		
		return {
			{"message", validRequests.at(requestId)}
		};
	}
}
