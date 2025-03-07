#pragma once

#include <string>
#include <functional>
#include "Timer.h"
#include "Logger.h"

namespace Gem {

    /**
     * @class ScopedTimer
     * @brief A timer that starts on construction and stops on destruction.
     *        It can log automatically or call a custom callback.
     */
    class ScopedTimer {
    public:
        /**
         * @brief Constructs a ScopedTimer that logs at the specified log level when destroyed.
         * @param name The name of the timer (for logging or debugging).
         * @param level The log level at which to print (default: Info).
         */
        explicit ScopedTimer(const std::string& name,
            Logger::LogLevel level = Logger::LogLevel::Info) noexcept;

        /**
         * @brief Constructs a ScopedTimer that calls a custom callback when destroyed.
         * @param name The name of the timer (for debugging).
         * @param callback A function that takes (name, elapsed_ms).
         */
        explicit ScopedTimer(const std::string& name,
            std::function<void(const std::string&, double)> callback) noexcept;

        ~ScopedTimer();

        // No copy/move
        ScopedTimer(const ScopedTimer&) = delete;
        ScopedTimer& operator=(const ScopedTimer&) = delete;
        ScopedTimer(ScopedTimer&&) = delete;
        ScopedTimer& operator=(ScopedTimer&&) = delete;

    private:
        Timer timer_;
        std::string name_;
        Logger::LogLevel logLevel_;
        bool useCallback_;
        std::function<void(const std::string&, double)> callback_;
    };

} // namespace Gem
