#pragma once
#include "logger/RequestLogger.h"
#include "logger/ResponseLogger.h"
#include "monitoring/SystemMonitor.h"

namespace global
{
	logger::RequestLogger requestLogger{};
	logger::ResponseLogger responseLogger{};

	monitoring::SystemMonitor systemMonitor{};
}
