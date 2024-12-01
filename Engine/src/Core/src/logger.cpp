#include "../logger.h"
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Gem {
    namespace Core {

        std::shared_ptr<spdlog::logger> Logger::logger_;

        void Logger::init() {
            // Create a color console sink
            logger_ = spdlog::stdout_color_mt("GemEngine");
            spdlog::set_pattern("[%T] [%^%L%$] %v");
            spdlog::set_level(spdlog::level::debug);
        }

        std::shared_ptr<spdlog::logger>& Logger::get_logger() {
            return logger_;
        }

    } // namespace Core
} // namespace Gem
