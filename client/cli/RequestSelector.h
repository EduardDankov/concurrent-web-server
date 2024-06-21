#include <string>

#include "../utils/Json.h"

namespace cli
{
	class RequestSelector
	{
	public:
		static nlohmann::json select();
	};
}
