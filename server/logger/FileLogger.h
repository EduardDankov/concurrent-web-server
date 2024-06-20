#pragma once
#include <fstream>

namespace logger
{
	class FileLogger
	{
	private:
		std::unique_ptr<std::ofstream> m_os;

	public:
		FileLogger(const std::filesystem::path& path);

		~FileLogger();

		static void createLogDir(const std::filesystem::path& path);

		void log(const std::string& message) const;
	};
}
