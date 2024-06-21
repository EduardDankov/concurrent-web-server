#include "pch.h"

#include <string>
#include <fstream>
#include <memory>
#include <filesystem>

#include "../server-win/logger/FileLogger.cpp"

TEST(FileLogger, isLoggingText)
{
	createTestFileDir();
	std::filesystem::path testPath = testFileDirPath / "FileLogger_isLoggingText.txt";

	const std::string testMessage = "Lorem ipsum dolor sit amet, consectetur adipiscing elit.";
	auto logger = logger::FileLogger(testPath);
	logger.log(testMessage);

	try
	{
		std::ifstream is(testPath, std::ifstream::binary);
		is.exceptions(std::ifstream::failbit);
		std::string fileContent;
		std::getline(is, fileContent);

		// remove carriage return if exists
		fileContent.erase(std::remove(fileContent.begin(), fileContent.end(), '\r'), fileContent.end());

		EXPECT_EQ(fileContent, testMessage);
	}
	catch (const std::exception& e)
	{
		FAIL() << e.what();
	}
}
