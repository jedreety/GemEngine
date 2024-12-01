#include "../scoped_timer.h"
#include "../../Core/logger.h"

namespace Gem {

	namespace Core {	

		std::mutex ScopedTimer::logMutex_;

		ScopedTimer::ScopedTimer(const std::string& name, int precision)
			: name_(name), timer_(), precision_(precision)
		{
			// Timer starts automatically upon construction
		}

		ScopedTimer::~ScopedTimer() {

			timer_.update();

			double elapsed = timer_.getElapsedMillis();

			std::lock_guard<std::mutex> lock(logMutex_);
			
			std::ostringstream oss;
			oss << std::fixed << std::setprecision(precision_) << elapsed;
			
			LOG_DEBUG("[SCOPED-TIMER] {0} ~ {1} ms", name_, oss.str());
		}

	} // namespace Core
} // namespace Gem
