#include <iostream>
#include <filesystem>

#include "FileLogger.h"

logger::FileLogger::FileLogger(const std::filesystem::path& path) : m_filePath(path)
{
	try
	{
		m_os = std::make_unique<std::ofstream>(path, std::fstream::out | std::fstream::app);
		m_os->exceptions(std::ofstream::failbit);
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
}

logger::FileLogger::~FileLogger()
{
	m_os->close();
}

void logger::FileLogger::createLogDir(const std::filesystem::path& path)
{
	if (std::filesystem::exists(path)) return;

	std::filesystem::create_directory(path);
}

void logger::FileLogger::log(const std::string& message) const
{
	*m_os << message << '\n';
	m_os->flush();
}
