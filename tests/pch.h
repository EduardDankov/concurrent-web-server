//
// pch.h
//

#pragma once

#include "gtest/gtest.h"

#include <filesystem>

const std::filesystem::path testFileDirPath = "test-files";

void createTestFileDir();
