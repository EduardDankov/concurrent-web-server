#pragma once
#include <fstream>

namespace logger
{
	class FileLogger
	{
	protected:
		std::unique_ptr<std::ofstream> m_os;

	public:
		FileLogger(const std::filesystem::path& path);

		virtual ~FileLogger();

		static void createLogDir(const std::filesystem::path& path);

		void log(const std::string& message) const;
	};
}
