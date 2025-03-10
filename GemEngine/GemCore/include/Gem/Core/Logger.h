#pragma once

#include <iostream>
#include <sstream>
#include <mutex>
#include <string>
#include <chrono>
#include <iomanip>

/**
 * If GEMENGINE_MIN_LOG_LEVEL is not defined by the build system,
 * default it to 0 (which means Debug).
 *
 * 0 = Debug
 * 1 = Info
 * 2 = Warning
 * 3 = Error
 */
#ifndef GEMENGINE_MIN_LOG_LEVEL

    #ifdef DIST
        #define GEMENGINE_MIN_LOG_LEVEL 3

    #elif defined(RELEASE)
        #define GEMENGINE_MIN_LOG_LEVEL 2

    #else
        #define GEMENGINE_MIN_LOG_LEVEL 0
        
    #endif
#endif

namespace Gem {

    class Logger {
    public:
        /**
         * @brief Enumeration for log levels.
         */
        enum class LogLevel {
            Debug = 0,
            Info = 1,
            Warning = 2,
            Error = 3
        };

        //--------------------------------------------------------------------------
        // 1) Runtime min log level
        //--------------------------------------------------------------------------
        /**
         * @brief Sets the runtime minimum log level.
         *        Any calls below this level won't print at runtime.
         */
        static void setMinLogLevel(LogLevel level) noexcept;

        /**
         * @brief Returns the currently set runtime minimum log level.
         */
        [[nodiscard]] static LogLevel getMinLogLevel() noexcept;

        //--------------------------------------------------------------------------
        // 2) Core log function with formatting
        //--------------------------------------------------------------------------
        /**
         * @brief Logs a message at a specified level with format placeholders "{}".
         *
         * This checks both compile-time and run-time thresholds.
         */
        template <typename... Args>
        static void log(LogLevel level, const std::string& format, Args... args) noexcept {
            // Compile-time filter (e.g., if GEMENGINE_MIN_LOG_LEVEL=2 and 'level' is Debug=0 or Info=1, skip entirely)
            if (static_cast<int>(level) < GEMENGINE_MIN_LOG_LEVEL) {
                return; // compiled out below threshold
            }

            // Run-time filter (useful if we compiled with debug but want to filter at runtime)
            if (level < getMinLogLevel()) {
                return;
            }

            // Format the message
            std::ostringstream stream;
            formatMessage(stream, format, args...);

            // Actually print the log
            logImpl(level, stream.str());
        }

        //--------------------------------------------------------------------------
        // 3) Convenience wrappers for each log level
        //--------------------------------------------------------------------------
        template <typename... Args>
        static void debug(const std::string& format, Args... args) noexcept {
            // Compile-time check
#if GEMENGINE_MIN_LOG_LEVEL <= 0
        // Run-time check
            if (LogLevel::Debug >= getMinLogLevel()) {
                logImpl(LogLevel::Debug, formatMessageString(format, args...));
            }
#endif
        }

        template <typename... Args>
        static void info(const std::string& format, Args... args) noexcept {
#if GEMENGINE_MIN_LOG_LEVEL <= 1
            if (LogLevel::Info >= getMinLogLevel()) {
                logImpl(LogLevel::Info, formatMessageString(format, args...));
            }
#endif
        }

        template <typename... Args>
        static void warning(const std::string& format, Args... args) noexcept {
#if GEMENGINE_MIN_LOG_LEVEL <= 2
            if (LogLevel::Warning >= getMinLogLevel()) {
                logImpl(LogLevel::Warning, formatMessageString(format, args...));
            }
#endif
        }

        template <typename... Args>
        static void error(const std::string& format, Args... args) noexcept {
#if GEMENGINE_MIN_LOG_LEVEL <= 3
            if (LogLevel::Error >= getMinLogLevel()) {
                logImpl(LogLevel::Error, formatMessageString(format, args...));
            }
#endif
        }

    private:
        //--------------------------------------------------------------------------
        // Implementation details
        //--------------------------------------------------------------------------
        Logger() = delete;  // no instances
        ~Logger() = delete;

        // This function actually prints to console (or file). No compile-time checks here.
        static void logImpl(LogLevel level, const std::string& message) noexcept;

        //--------------------------------------------------------------------------
        // 4) Formatting
        //--------------------------------------------------------------------------
        // For direct usage in log():
        template <typename... Args>
        static void formatMessage(std::ostringstream& stream, const std::string& format, Args... args) noexcept {
            stream << formatMessageString(format, args...);
        }

        // For usage in debug()/info()/warning()/error() macros
        // that build a single string.
        static std::string formatMessageString(const std::string& format) noexcept {
            return format;
        }

        template<typename T, typename... Args>
        static std::string formatMessageString(const std::string& format, T value, Args... args) noexcept {
            size_t pos = format.find("{}");
            if (pos != std::string::npos) {
                std::ostringstream stream;
                // Output everything before "{}"
                stream << format.substr(0, pos);
                // Insert the argument
                stream << value;
                // Recursively format the rest
                stream << formatMessageString(format.substr(pos + 2), args...);
                return stream.str();
            }
            else {
                // No more placeholders
                return format;
            }
        }

        //--------------------------------------------------------------------------
        // 5) Helpers for time / level strings
        //--------------------------------------------------------------------------
        [[nodiscard]] static std::string getCurrentTime() noexcept;
        [[nodiscard]] static std::string logLevelToString(LogLevel level) noexcept;

        //--------------------------------------------------------------------------
        // 6) Shared data
        //--------------------------------------------------------------------------
        static std::mutex log_mutex_;
        static LogLevel min_log_level_; // runtime min log level
    };

} // namespace Gem
