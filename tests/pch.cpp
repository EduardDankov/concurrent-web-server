//
// pch.cpp
//

#include "pch.h"

void createTestFileDir()
{
	if (std::filesystem::exists(testFileDirPath)) return;

	std::filesystem::create_directory(testFileDirPath);
}
