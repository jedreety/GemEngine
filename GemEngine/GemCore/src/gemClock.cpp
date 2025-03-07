#include <Gem/Core/Clock.h>
#include <Gem/Core/Logger.h>
#include <algorithm>

namespace Gem {

    Clock::Clock() noexcept
        : previous_time_(ClockType::now())
        , current_time_(ClockType::now())
        , delta_time_(0.0)
        , frame_count_(0)
        , fps_timer_(0.0)
        , fps_log_interval_(0.0)
        , last_average_fps_(0.0)
    {
    }

    void Clock::update(int max_fps) noexcept {
        std::lock_guard<std::mutex> lock(mutex_);

        current_time_ = ClockType::now();
        std::chrono::duration<double> frame_duration = current_time_ - previous_time_;
        delta_time_ = frame_duration.count();
        previous_time_ = current_time_;

        // FPS logging logic
        frame_count_++;
        fps_timer_ += delta_time_;

        if (fps_log_interval_ > 0.0 && fps_timer_ >= fps_log_interval_) {
            // Compute average FPS
            double avg_fps = frame_count_ / fps_timer_;
            last_average_fps_ = avg_fps;

            Gem::Logger::info("[Clock] ~ AVG FPS: {}", avg_fps);

            // Reset counters
            frame_count_ = 0;
            fps_timer_ = 0.0;
        }

        // Cap FPS if needed
        if (max_fps > 0) {
            double target_frame = 1.0 / static_cast<double>(max_fps);
            if (delta_time_ < target_frame) {
                double sleep_time = target_frame - delta_time_;
                
                // Simple approach:
                // std::this_thread::sleep_for(std::chrono::duration<double>(sleep_time));

                // More precise approach
                auto wakeUp = ClockType::now() + std::chrono::duration<double>(sleep_time);
                while (ClockType::now() < wakeUp) {
                    std::this_thread::sleep_for(std::chrono::microseconds(50));
                }
            }
        }
    }

    void Clock::logFPS(int interval_seconds) noexcept {
        std::lock_guard<std::mutex> lock(mutex_);
        fps_log_interval_ = static_cast<double>(interval_seconds);
        // Reset so we don't mix intervals
        fps_timer_ = 0.0;
        frame_count_ = 0;
        last_average_fps_ = 0.0;
    }

    double Clock::getDeltaTime() const noexcept {
        std::lock_guard<std::mutex> lock(mutex_);
        return delta_time_;
    }

    double Clock::getInstantFPS() const noexcept {
        std::lock_guard<std::mutex> lock(mutex_);
        if (delta_time_ > 0.0) {
            return 1.0 / delta_time_;
        }
        return 0.0;
    }

    double Clock::getAverageFPS() const noexcept {
        std::lock_guard<std::mutex> lock(mutex_);
        return last_average_fps_;
    }

} // namespace Gem
