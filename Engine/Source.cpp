#include <iostream>

// Check in project proprety: VC++ DIRECTORIES -> Include Directories that you have the right library

// Core functionality
#include <Gem/Core/GemEngine.h>
#include <Gem/Core/Logger.h>
#include <Gem/Core/Clock.h>
#include <Gem/Core/Timer.h>
#include <Gem/Core/ScopedTimer.h>

// Window
#include <Gem/Window/Window.h>

// GLFW callback
void onFramebufferResized(GLFWwindow* window, int width, int height) {
    Gem::Logger::info("Framebuffer resized callback: {}x{}", width, height);
}

int main() {

    try {
        //---------------------------------------------------------------------
        // 1) Configure Logger
        //---------------------------------------------------------------------
        // For demonstration, let's compile-time set GEMENGINE_MIN_LOG_LEVEL=0 (Debug)
        // Then at runtime, we can still set the min log level:
        Gem::Logger::setMinLogLevel(Gem::Logger::LogLevel::Debug);

        // Show an example of every log level
        Gem::Logger::debug("This is a debug log. Debug level: {}", 123);
        Gem::Logger::info("This is an info log with string: {}", "GemEngine starting...");
        Gem::Logger::warning("This is a warning log, watch out!");
        Gem::Logger::error("This is an error log, handle carefully.");

        //---------------------------------------------------------------------
        // 2) Initialize Vulkan
        //---------------------------------------------------------------------
        Gem::Logger::info("Initializing GemEngine (Vulkan)...");
        Gem::GemEngine::getInstance().init();  // Will skip if already inited
        Gem::Logger::info("GemEngine initialized successfully.");

        //---------------------------------------------------------------------
        // 3) Clock usage: measure FPS, optional capping
        //---------------------------------------------------------------------
        Gem::Clock clock;
        // Log average FPS every 2 seconds
        clock.logFPS(2);

        //---------------------------------------------------------------------
        // 4) Create a window
        //---------------------------------------------------------------------
        Gem::Window window(800, 600, "GemEngine Window");
        window.setFramebufferSizeCallback(onFramebufferResized);

        //---------------------------------------------------------------------
        // 5) Timer usage
        //---------------------------------------------------------------------
        Gem::Timer timer;
        timer.start(); // Start measuring from now
        Gem::Logger::info("Timer started.");

        // We'll also demonstrate pausing/unpausing
        timer.pause(); // Immediately pause to show usage
        Gem::Logger::info("Timer paused right away: elapsed so far = {} ms", timer.getElapsedTimeInMilliseconds());

        timer.unpause();
        Gem::Logger::info("Timer unpaused.");

        //---------------------------------------------------------------------
        // 6) ScopedTimer usage (lifetime in this local scope)
        //---------------------------------------------------------------------
        {
            Gem::ScopedTimer scopeTimer("Initialization Scope", Gem::Logger::LogLevel::Info);
            // The destructor will log the time once we exit this block
        }

        //---------------------------------------------------------------------
        // 7) Main Loop (simulate 5 seconds)
        //---------------------------------------------------------------------
        const double maxDurationSeconds = 5.0; // We'll exit after ~5 seconds
        double accumulatedTime = 0.0;

        // If you want to limit FPS to 60, pass `60` to clock.update().
        while (!window.shouldClose()) {
            // Update clock (optionally cap FPS)
            clock.update(60);

            // Pause or do something:
            double dt = clock.getDeltaTime(); // in seconds
            accumulatedTime += dt;

            // Occasionally demonstrate logging at runtime
            if (accumulatedTime > 2.0 && accumulatedTime < 2.1) {
                Gem::Logger::debug("2 seconds have passed. Instant FPS: {}", clock.getInstantFPS());
            }
            if (accumulatedTime > 4.0 && accumulatedTime < 4.1) {
                Gem::Logger::info("4 seconds have passed. Elapsed timer (ms): {}", timer.getElapsedTimeInMilliseconds());
            }

            // If we've run more than 5 seconds, break out
            if (accumulatedTime >= maxDurationSeconds) {
                Gem::Logger::info("Reached 5 seconds, exiting main loop.");
                break;
            }

            // Poll GLFW events so the window can update
            glfwPollEvents();
        }

        // Stop the timer and log final time
        timer.stop();
        Gem::Logger::info("Timer stopped. Total elapsed: {} ms", timer.getElapsedTimeInMilliseconds());

    }
    catch (const std::exception& e) {
        Gem::Logger::error("Exception caught: {}", e.what());
        return EXIT_FAILURE;
    }

    return 0;
}