#include <filesystem>

namespace constants
{
	const std::filesystem::path logDirPath = "logs";
	const std::filesystem::path requestLogPath = logDirPath / "request_log.txt";
	const std::filesystem::path responseLogPath = logDirPath / "response_log.txt";
}
