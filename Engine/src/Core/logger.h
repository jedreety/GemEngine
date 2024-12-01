#pragma once

#include <spdlog/spdlog.h>
#include <memory>

namespace Gem {
    namespace Core {

        /**
         * @brief Logger class for the Gem Engine.
         *
         * This class initializes and provides access to the logger.
         * It uses the spdlog library for logging.
         */
        class Logger {
        public:
            /**
             * @brief Initializes the logger.
             *
             * Sets up the logging pattern and default logging level.
             */
            static void init();

            /**
             * @brief Retrieves the logger instance.
             *
             * @return Shared pointer to the spdlog logger.
             */
            static std::shared_ptr<spdlog::logger>& get_logger();

        private:
            static std::shared_ptr<spdlog::logger> logger_; ///< Logger instance.
        };

    } // namespace Core
} // namespace Gem

// Logging macros for convenience
#define LOG_TRACE(...)    ::Gem::Core::Logger::get_logger()->trace(__VA_ARGS__)
#define LOG_DEBUG(...)    ::Gem::Core::Logger::get_logger()->debug(__VA_ARGS__)
#define LOG_INFO(...)     ::Gem::Core::Logger::get_logger()->info(__VA_ARGS__)
#define LOG_WARN(...)     ::Gem::Core::Logger::get_logger()->warn(__VA_ARGS__)
#define LOG_ERROR(...)    ::Gem::Core::Logger::get_logger()->error(__VA_ARGS__)
#define LOG_CRITICAL(...) ::Gem::Core::Logger::get_logger()->critical(__VA_ARGS__)
