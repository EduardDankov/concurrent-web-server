#pragma once
#include <filesystem>

namespace constants
{
	const std::string serverVersion = "0.1";

	const std::filesystem::path logDirPath = "logs";
	const std::filesystem::path requestLogPath = logDirPath / "request_log.txt";
	const std::filesystem::path responseLogPath = logDirPath / "response_log.txt";

	const std::string serverAddr = "127.0.0.1";
	const int serverPort = 3579;
	const size_t threadPoolSize = 16;
	const size_t backlogSize = 128;
	const size_t bufferSize = 4096;
}
