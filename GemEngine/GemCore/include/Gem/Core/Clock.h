#pragma once

#include <chrono>
#include <thread>
#include <mutex>

namespace Gem {

    /**
     * @class Clock
     * @brief A utility class for managing delta time, printing FPS,
     *        and capping FPS in a game loop.
     */
    class Clock {
    public:
        using ClockType = std::chrono::steady_clock;
        using TimePoint = std::chrono::time_point<ClockType>;

        /**
         * @brief Constructs a Clock instance.
         */
        explicit Clock() noexcept;

        /**
         * @brief Updates the clock, calculates delta time, caps FPS, logs FPS.
         * @param max_fps Maximum FPS to cap (0 = no cap).
         */
        void update(int max_fps = 0) noexcept;

        /**
         * @brief Sets the interval in seconds for logging FPS. (0 = disable logs)
         */
        void logFPS(int interval_seconds) noexcept;

        /**
         * @brief Returns the time elapsed between the previous frame and this frame (in seconds).
         */
        [[nodiscard]] double getDeltaTime() const noexcept;

        /**
         * @brief Instantaneous FPS = 1.0 / deltaTime.
         */
        [[nodiscard]] double getInstantFPS() const noexcept;

        /**
         * @brief Average FPS over the last log interval (if the interval is set).
         *
         * If the interval isn’t set or not reached yet, returns the most recent calculation.
         */
        [[nodiscard]] double getAverageFPS() const noexcept;

        // Delete copy/move
        Clock(const Clock&) = delete;
        Clock& operator=(const Clock&) = delete;
        Clock(Clock&&) = delete;
        Clock& operator=(Clock&&) = delete;

    private:
        mutable std::mutex mutex_;
        TimePoint previous_time_;
        TimePoint current_time_;

        double delta_time_;       ///< Seconds between frames
        int frame_count_;         ///< Number of frames in the current interval
        double fps_timer_;        ///< How many seconds have passed in the current interval
        double fps_log_interval_; ///< Interval length in seconds
        double last_average_fps_; ///< Last computed average FPS
    };

} // namespace Gem
