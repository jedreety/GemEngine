#pragma once

#include <chrono>
#include <mutex>

/**
 * @file Timer.h
 * @brief Declaration of the Timer class for time tracking.
 */

namespace Gem {
    namespace Core {

        /**
         * @class Timer
         * @brief Utility class for managing and tracking elapsed time.
         *
         * Provides functionality to track the total elapsed time since the timer was started.
         */
        class Timer {

        public:
            
            using Clock = std::chrono::steady_clock;
            using TimePoint = std::chrono::time_point<Clock>;

        public:
        
            /**
             * @brief Constructs a new Timer object and starts the timer.
             */
            Timer();

            /**
             * @brief Starts or restarts the timer.
             *
             * Resets the start time point to the current time and resets elapsed time.
             */
            void start();

            /**
             * @brief Updates the timer by calculating the elapsed time.
             *
             * Should be called once per frame or at regular intervals to keep track of time progression.
             */
            void update();

            /**
             * @brief Retrieves the total elapsed time since the timer was started.
             * @return Total elapsed time in seconds.
             */
            double getElapsedTime() const;

            /**
             * @brief Retrieves the total elapsed time in milliseconds.
             * @return Total elapsed time in milliseconds.
             */
            double getElapsedMillis() const;

            // Delete copy constructor and copy assignment operator
            Timer(const Timer&) = delete;
            Timer& operator=(const Timer&) = delete;

            // Delete move constructor and move assignment operator
            Timer(Timer&&) = delete;
            Timer& operator=(Timer&&) = delete;


        private:

            mutable std::mutex mutex_;    ///< Mutex to protect shared data.

            TimePoint startTime_;         ///< The time point when the timer was started.

            double elapsedTime_;          ///< Total elapsed time in seconds.

        };

    } // namespace Core
} // namespace Gem
