#pragma once

#include <chrono>
#include <mutex>

namespace Gem {

    /**
     * @class Timer
     * @brief A thread-safe utility class for measuring elapsed time
     *        with start, stop, pause, and reset functionality.
     */
    class Timer {
    public:
        using ClockType = std::chrono::steady_clock;
        using TimePoint = std::chrono::time_point<ClockType>;

        /**
         * @brief Constructs a new timer instance, not running by default.
         */
        explicit Timer() noexcept;

        /**
         * @brief Starts or restarts the timer from zero.
         *        If already running, resets elapsed time to 0 and continues running.
         */
        void start() noexcept;

        /**
         * @brief Stops the timer (so elapsed time stops accumulating).
         */
        void stop() noexcept;

        /**
         * @brief Pauses the timer (elapsed time stops accumulating),
         *        but does not reset the current elapsed time.
         */
        void pause() noexcept;

        /**
         * @brief Unpauses the timer (resumes accumulation from the current elapsed time).
         */
        void unpause() noexcept;

        /**
         * @brief Resets the timer. By default, it remains stopped after resetting.
         *
         * @param keepRunning If true, the timer immediately restarts after reset.
         */
        void reset(bool keepRunning = false) noexcept;

        /**
         * @brief Gets the elapsed time in seconds.
         */
        [[nodiscard]] double getElapsedTimeInSeconds() const noexcept;

        /**
         * @brief Gets the elapsed time in milliseconds.
         */
        [[nodiscard]] double getElapsedTimeInMilliseconds() const noexcept {
            return getElapsedTimeInSeconds() * 1000.0;
        }

        /**
         * @brief Checks if the timer is currently running (not stopped, not paused).
         */
        [[nodiscard]] bool isRunning() const noexcept;

        /**
         * @brief Checks if the timer is paused (i.e., time not currently accumulating).
         */
        [[nodiscard]] bool isPaused() const noexcept;

        // Delete copy/move
        Timer(const Timer&) = delete;
        Timer& operator=(const Timer&) = delete;
        Timer(Timer&&) = delete;
        Timer& operator=(Timer&&) = delete;

    private:
        mutable std::mutex mutex_;
        TimePoint start_time_;
        TimePoint pause_time_;   ///< When we last paused the timer.
        double accumulated_time_; ///< Elapsed time stored when paused/stopped.

        bool is_running_;  ///< True if actively accumulating time.
        bool is_paused_;   ///< True if paused (not accumulating), but has some stored time.
    };

} // namespace Gem
