#pragma once

#include <string>
#include <iostream>
#include <iomanip>
#include <mutex>
#include "timer.h"

/**
 * @file scoped_timer.h
 * @brief Declaration of the ScopedTimer class.
 */

namespace Gem {

    namespace Core {

        /**
         * @class ScopedTimer
         * @brief RAII class for timing the duration of a scoped block.
         *
         * Starts a timer upon construction and logs the elapsed time upon destruction.
         */
        class ScopedTimer {

        public:

            /**
             * @brief Constructs a ScopedTimer with a given name.
             * @param name The identifier for the timed scope.
             * @param precision Number of digits shown.
             */
            explicit ScopedTimer(const std::string& name, int precision = 3);

            // Delete copy constructor and copy assignment to prevent copying
            ScopedTimer(const ScopedTimer&) = delete;
            ScopedTimer& operator=(const ScopedTimer&) = delete;

			// Delete move constructor and move assignment operator
			ScopedTimer(ScopedTimer&&) = delete;
			ScopedTimer& operator=(ScopedTimer&&) = delete;

            /**
             * @brief Destructs the ScopedTimer and logs the elapsed time.
             *
             * Upon destruction, the timer is updated and the elapsed time is logged to the console.
             */
            ~ScopedTimer();

        private:

            std::string name_;              ///< The name of the timed scope.
            Timer timer_;                   ///< The timer instance tracking elapsed time.
            static std::mutex logMutex_;    ///< Mutex to protect logging output.
            int precision_;                 ///< The timer output precision
        };

    } // namespace Core
} // namespace Gem
