#include "../timer.h"

namespace Gem {
    namespace Core {

        Timer::Timer() {

            start();
        }

        void Timer::start() {
			
            std::lock_guard<std::mutex> lock(mutex_);

            startTime_ = Clock::now();
            elapsedTime_ = 0.0;
        }

        void Timer::update() {

            std::lock_guard<std::mutex> lock(mutex_);
            TimePoint currentTime = Clock::now();

            // Calculate Elapsed Time
            elapsedTime_ = std::chrono::duration<double>(currentTime - startTime_).count();
        }

        double Timer::getElapsedTime() const {

            std::lock_guard<std::mutex> lock(mutex_);
            return elapsedTime_;
        }

        double Timer::getElapsedMillis() const {
			
            std::lock_guard<std::mutex> lock(mutex_);
            return elapsedTime_ * 1000.0;
        }

    } // namespace Core
} // namespace Gem
