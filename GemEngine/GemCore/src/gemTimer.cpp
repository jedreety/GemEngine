#include <Gem/Core/Timer.h>

namespace Gem {

    Timer::Timer() noexcept
        : start_time_(ClockType::now())
        , pause_time_(ClockType::now())
        , accumulated_time_(0.0)
        , is_running_(false)
        , is_paused_(false)
    {
    }

    void Timer::start() noexcept {
        std::lock_guard<std::mutex> lock(mutex_);

        is_running_ = true;
        is_paused_ = false;
        accumulated_time_ = 0.0;  // Reset any previous elapsed
        start_time_ = ClockType::now();
    }

    void Timer::stop() noexcept {
        std::lock_guard<std::mutex> lock(mutex_);

        if (is_running_) {
            // If we're paused, 'accumulated_time_' already holds the final elapsed.
            // If we're running and not paused, we finalize it now.
            if (!is_paused_) {
                auto now = ClockType::now();
                std::chrono::duration<double> delta = now - start_time_;
                accumulated_time_ += delta.count();
            }
            is_running_ = false;
            is_paused_ = false;
        }
    }

    void Timer::pause() noexcept {
        std::lock_guard<std::mutex> lock(mutex_);

        if (is_running_ && !is_paused_) {
            // Accumulate time so far
            auto now = ClockType::now();
            std::chrono::duration<double> delta = now - start_time_;
            accumulated_time_ += delta.count();
            // Mark paused
            pause_time_ = now;
            is_paused_ = true;
        }
    }

    void Timer::unpause() noexcept {
        std::lock_guard<std::mutex> lock(mutex_);
        if (is_running_ && is_paused_) {
            // Resume from now
            is_paused_ = false;
            start_time_ = ClockType::now();
        }
    }

    void Timer::reset(bool keepRunning) noexcept {
        std::lock_guard<std::mutex> lock(mutex_);

        accumulated_time_ = 0.0;
        start_time_ = ClockType::now();
        pause_time_ = start_time_;
        is_paused_ = false;

        if (keepRunning) {
            is_running_ = true;
        }
        else {
            is_running_ = false;
        }
    }

    double Timer::getElapsedTimeInSeconds() const noexcept {
        std::lock_guard<std::mutex> lock(mutex_);

        if (!is_running_) {
            // Timer is stopped => just return whatever was accumulated
            return accumulated_time_;
        }

        if (is_paused_) {
            // Timer is paused => also return the accumulated time
            return accumulated_time_;
        }

        // Timer is running and not paused => calculate
        auto now = ClockType::now();
        std::chrono::duration<double> delta = now - start_time_;
        return accumulated_time_ + delta.count();
    }

    bool Timer::isRunning() const noexcept {
        std::lock_guard<std::mutex> lock(mutex_);
        return is_running_ && !is_paused_;
    }

    bool Timer::isPaused() const noexcept {
        std::lock_guard<std::mutex> lock(mutex_);
        return is_paused_;
    }

} // namespace Gem
