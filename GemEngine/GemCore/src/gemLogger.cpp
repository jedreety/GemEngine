#include <Gem/Core/Logger.h>
#include <ctime>   // for std::time_t, localtime, strftime

#pragma warning( disable : 4996 ) // Disable warning about std::localtime being unsafe

namespace Gem {

    std::mutex Logger::log_mutex_;
    Logger::LogLevel Logger::min_log_level_ = Logger::LogLevel::Debug;

    //------------------------------------------------------------------------------
    // 1) Set/Get runtime log level
    //------------------------------------------------------------------------------
    void Logger::setMinLogLevel(LogLevel level) noexcept {
        std::lock_guard<std::mutex> lock(log_mutex_);
        min_log_level_ = level;
    }

    Logger::LogLevel Logger::getMinLogLevel() noexcept {
        std::lock_guard<std::mutex> lock(log_mutex_);
        return min_log_level_;
    }

    //------------------------------------------------------------------------------
    // 2) logImpl() - Actual printing
    //------------------------------------------------------------------------------
    void Logger::logImpl(LogLevel level, const std::string& message) noexcept {
        // Acquire the lock to ensure thread-safe printing
        std::lock_guard<std::mutex> lock(log_mutex_);

        // Build final log line
        std::string timeStr = getCurrentTime();
        std::string levelStr = logLevelToString(level);

        // (Optional) Add color codes if you like:
        // e.g., for ANSI terminals:
        std::string colorCode;
        switch (level) {
        case LogLevel::Debug:   colorCode = "\033[36m"; break; // cyan
        case LogLevel::Info:    colorCode = "\033[32m"; break; // green
        case LogLevel::Warning: colorCode = "\033[33m"; break; // yellow
        case LogLevel::Error:   colorCode = "\033[31m"; break; // red
        }
        const std::string resetCode = "\033[0m";

        // Print to standard output (you could also print to a file, etc.)
        std::cout << colorCode
            << "[" << timeStr << "] "
            << "[" << levelStr << "] "
            << message
            << resetCode
            << std::endl;
    }

    //------------------------------------------------------------------------------
    // 3) getCurrentTime()
    //------------------------------------------------------------------------------
    std::string Logger::getCurrentTime() noexcept {
        // Using system_clock for a local time string
        auto now = std::chrono::system_clock::now();
        std::time_t now_c = std::chrono::system_clock::to_time_t(now);

        // Format like "2025-01-18 12:34:56"
        char buffer[20];
        std::tm* timeinfo = std::localtime(&now_c);
        std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);

        return buffer;
    }

    //------------------------------------------------------------------------------
    // 4) logLevelToString()
    //------------------------------------------------------------------------------
    std::string Logger::logLevelToString(LogLevel level) noexcept {
        switch (level) {
        case LogLevel::Debug:   return "DEBUG";
        case LogLevel::Info:    return "INFO";
        case LogLevel::Warning: return "WARN";
        case LogLevel::Error:   return "ERROR";
        }
        return "UNKNOWN";
    }

} // namespace Gem
