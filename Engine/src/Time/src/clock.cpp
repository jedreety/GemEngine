#include "../Clock.h"
#include <iostream>
#include <thread>
#include <SDL2/SDL.h>
#include "../../Core/logger.h"

namespace Gem {
    namespace Core {

        Clock::Clock()
            : deltaTime_(0.0),
              fpsAccumulator_(0.0f),
              frameCount_(0),
              debugFps_(0.0) {

            lastTime_ = ClockType::now();
        }

        void Clock::update(double maxFps) {
            // Calculate Delta Time
            TimePoint currentTime = ClockType::now();

            {
                std::lock_guard<std::mutex> lock(mutex_);

                deltaTime_ = std::chrono::duration<double>(currentTime - lastTime_).count();
                lastTime_ = currentTime;
            }

            // FPS Capping (Performed Outside Mutex)
            if (maxFps > 0.0) {

                double desiredFrameTime = 1.0 / maxFps;

                if (deltaTime_ < desiredFrameTime) {

                    double sleepTime = desiredFrameTime - deltaTime_;
                    // Convert sleepTime to milliseconds
                    Uint32 sleepTimeMs = static_cast<Uint32>(sleepTime * 1000.0);
                    SDL_Delay(sleepTimeMs);

                    // After Delay: Update Timing
                    currentTime = ClockType::now();

                    {
                        std::lock_guard<std::mutex> lock(mutex_);

                        // Recalculate Delta Time including sleep duration
                        deltaTime_ = std::chrono::duration<double>(currentTime - lastTime_).count();
                        lastTime_ = currentTime;
                    }
                }
            }

            // FPS Logging
            if (debugFps_ > 0.0) {

                std::lock_guard<std::mutex> lock(mutex_);

                frameCount_++;
                fpsAccumulator_ += deltaTime_;

                if (fpsAccumulator_ >= debugFps_) {

                    double fps = static_cast<double>(frameCount_) / fpsAccumulator_;

                    std::ostringstream oss;
			        oss << std::fixed << std::setprecision(precision_) << fps;

                    LOG_DEBUG("[CLOCK] Debug FPS ~ {0} fps", oss.str());

                    frameCount_ = 0;
                    fpsAccumulator_ = 0.0f;
                }
            }
        }
        double Clock::getDeltaTime() const {

            std::lock_guard<std::mutex> lock(mutex_);
            return deltaTime_;
        }

        double Clock::getDeltaMillis() const {

            std::lock_guard<std::mutex> lock(mutex_);
            return deltaTime_ * 1000.0;
        }

        void Clock::set_debugFps(unsigned int debugFps, int precision) {

            std::lock_guard<std::mutex> lock(mutex_);
            debugFps_ = debugFps;
            precision_ = precision;
        }

    } // namespace Core
} // namespace Gem
