#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <mutex>

namespace Gem {

    /**
     * @class GLFWManager
     * @brief A singleton manager that handles the global initialization and termination of GLFW.
     *
     *        Uses reference counting so that multiple Window objects can be created without
     *        re-initializing or prematurely terminating GLFW.
     */
    class GLFWManager
    {
    public:
        /**
         * @brief Gets the singleton instance of GLFWManager.
         *
         * @return Reference to the GLFWManager instance.
         */
        static GLFWManager& getInstance();

        // Delete copy/move operations to enforce singleton usage.
        GLFWManager(const GLFWManager&) = delete;
        GLFWManager(GLFWManager&&) = delete;
        GLFWManager& operator=(const GLFWManager&) = delete;
        GLFWManager& operator=(GLFWManager&&) = delete;

        /**
         * @brief Initializes GLFW.
         */
        void initGLFW();

        /**
         * @brief Terminates GLFW if initialized.
         */
        void terminateGLFW();


    private:
        GLFWManager() = default;  ///< Private constructor to ensure singleton usage.
        ~GLFWManager() = default; ///< Private destructor.

        /**
         * @brief Increments the reference count for GLFW usage.
         *
         * If GLFW is not yet initialized, it initializes it.
         */
        void incrementRefCount();

        /**
         * @brief Decrements the reference count for GLFW usage.
         *
         * If the reference count hits zero, GLFW is terminated.
         */
        void decrementRefCount();

    private:
        std::mutex mutex_;      ///< Mutex to guard refCount_ and init/terminate operations.
        bool initialized_ = false;
        int refCount_ = 0;
    };

} // namespace Gem
