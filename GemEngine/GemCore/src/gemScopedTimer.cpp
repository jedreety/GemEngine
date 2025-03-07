#include <Gem/Core/ScopedTimer.h>

namespace Gem {

    ScopedTimer::ScopedTimer(const std::string& name,
        Logger::LogLevel level) noexcept
        : timer_()
        , name_(name)
        , logLevel_(level)
        , useCallback_(false)
        , callback_(nullptr)
    {
        timer_.start();
    }

    ScopedTimer::ScopedTimer(const std::string& name,
        std::function<void(const std::string&, double)> callback) noexcept
        : timer_()
        , name_(name)
        , logLevel_(Logger::LogLevel::Info)
        , useCallback_(true)
        , callback_(std::move(callback))
    {
        timer_.start();
    }

    ScopedTimer::~ScopedTimer() {
        timer_.stop();
        double elapsed_ms = timer_.getElapsedTimeInMilliseconds();

        if (useCallback_ && callback_) {
            // Call custom callback
            callback_(name_, elapsed_ms);
        }
        else {
            // Log at chosen level
            Logger::log(logLevel_, "[ScopedTimer] #{} ~ elapsed time: {} ms", name_, elapsed_ms);
        }
    }

} // namespace Gem
