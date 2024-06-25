#include "SystemMonitor.h"

namespace monitoring
{
	class SystemMonitorFactory
	{
	public:
		static std::shared_ptr<SystemMonitor> createSystemMonitor();
	};
}
