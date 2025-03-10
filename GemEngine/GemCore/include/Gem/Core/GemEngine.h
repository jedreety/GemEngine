#pragma once

#include <mutex>

namespace Gem {

    /**
     * @class GemEngine
     * @brief A singleton engine class that manages OpenGL and GLFW initialization.
     *
     * This class provides a centralized way to initialize and manage the graphics
     * subsystems required by the application. It uses reference counting to ensure
     * proper initialization and cleanup.
     */
    class GemEngine
    {
    public:
        /**
         * @brief Gets the singleton instance of GemEngine.
         *
         * @return Reference to the GemEngine instance.
         */
        static GemEngine& getInstance();

        // Delete copy/move operations to enforce singleton usage.
        GemEngine(const GemEngine&) = delete;
        GemEngine(GemEngine&&) = delete;
        GemEngine& operator=(const GemEngine&) = delete;
        GemEngine& operator=(GemEngine&&) = delete;

        /**
         * @brief Initializes OpenGL and GLFW.
         * 
         * If already initialized, this call will be skipped.
         * 
         * @return true if initialization was successful or already initialized, false otherwise.
         */
        bool init();

        /**
         * @brief Shuts down OpenGL and GLFW.
         * 
         * Decrements the reference count and cleans up resources when the count reaches zero.
         */
        void shutdown();

        /**
         * @brief Checks if the engine is initialized.
         * 
         * @return true if initialized, false otherwise.
         */
        bool isInitialized() const;

        /**
         * @brief Checks if the engine is running.
         *
         * This function is used to control the main game loop. The loop should
         * continue running as long as this function returns true.
         *
         * @return true if the engine is running, false otherwise.
         */
        bool isRunning();

        /**
         * @brief Exits the main loop and shuts down the engine.
         *
         * This function signals the engine to exit the main loop, cleans up
         * all resources, and terminates the program. After calling this,
         * isRunning() will return false.
         */
        void exit();

    private:
        GemEngine() = default;  ///< Private constructor to ensure singleton usage.
        ~GemEngine() = default; ///< Private destructor.

        /**
         * @brief Initializes OpenGL.
         * 
         * @return true if successful, false otherwise.
         */
        bool initOpenGL();

    private:

        std::mutex mutex_;      ///< Mutex to guard initialization and shutdown operations.
        bool initialized_ = false; ///< Flag indicating if the engine is initialized.
        bool running_ = false;      ///< Flag indicating if the engine is running.
    };

} // namespace Gem