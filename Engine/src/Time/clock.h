#pragma once

#include <chrono>
#include <mutex>

/**
 * @file Clock.h
 * @brief Declaration of the Clock class for frame timing and FPS control.
 */

namespace Gem {
    namespace Core {

        /**
         * @class Clock
         * @brief Utility class for managing frame timing, delta time, and FPS capping/logging.
         *
         * Provides functionality to track the time elapsed between consecutive updates (delta time),
         * cap the frame rate to a specified maximum FPS, and optionally log the FPS at regular intervals.
         */
        class Clock {

        public:
            
            using ClockType = std::chrono::steady_clock;
            using TimePoint = std::chrono::time_point<ClockType>;

        public:

            /**
             * @brief Constructs a new Clock object and initializes the timing.
             */
            Clock();

            /**
             * @brief Updates the clock by calculating the delta time and optionally caps the FPS.
             *
             * This function should be called once per frame or at regular intervals to keep track of time progression.
             * It calculates the time elapsed since the last update (delta time) and, if a maximum FPS is specified,
             * introduces a delay to cap the frame rate. Note that due to system limitations on sleep functions,
             * there is a practical upper limit on the maximum FPS that can be effectively enforced.
             *
             * @param maxFps Optional maximum FPS to cap the frame rate. If set to 0, no FPS cap is applied.
             *               Note: Capping FPS to values significantly higher than the system's timer resolution (usually around 1000 FPS)
             *               may not work as expected due to the limitations of sleep functions like SDL_Delay, which cannot delay
             *               for periods shorter than 1 millisecond.
             */
            void update(double maxFps = 0.0);

            /**
             * @brief Retrieves the time elapsed since the last update.
             * @return Delta time in seconds.
             */
            double getDeltaTime() const;

            /**
             * @brief Retrieves the delta time in milliseconds.
             * @return Delta time in milliseconds.
             */
            double getDeltaMillis() const;

            /**
             * @brief Sets the interval in seconds at which the FPS is logged.
             *
             * If set to a value greater than zero, the Clock will print the current FPS
             * to the console every `debugFps` seconds during each update.
             *
             * @param debugFps The interval in seconds for FPS logging.
             * @param precision Number of digits shown.
             */
            void set_debugFps(unsigned int debugFps, int precision = 0);

            // Delete copy constructor and copy assignment operator
            Clock(const Clock&) = delete;
            Clock& operator=(const Clock&) = delete;

            // Delete move constructor and move assignment operator
            Clock(Clock&&) = delete;
            Clock& operator=(Clock&&) = delete;


        private:

            mutable std::mutex mutex_;    ///< Mutex to protect shared data.

            TimePoint lastTime_;          ///< The time point at the last update.

            double deltaTime_;            ///< Delta time in seconds.

            float fpsAccumulator_;        ///< Accumulator for tracking elapsed time for FPS calculation.
            int frameCount_;              ///< Counts the number of frames within the FPS interval.
            double debugFps_;             ///< Interval in seconds to print the FPS. Set to 0 to disable FPS logging.

            int precision_;               ///< The Debug output precision

        };

    } // namespace Core
} // namespace Gem
