#pragma once
#include "logger/RequestLogger.h"
#include "logger/ResponseLogger.h"

namespace global
{
	logger::RequestLogger requestLogger{};
	logger::ResponseLogger responseLogger{};
}