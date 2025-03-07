#include <GLFW_Manager.h>
#include <Gem/Core/Logger.h>
#include <stdexcept>

namespace Gem {

    GLFWManager& GLFWManager::getInstance() {

        static GLFWManager instance;
        return instance;
    }

    void GLFWManager::incrementRefCount() {

        std::lock_guard<std::mutex> lock(mutex_);

        // If not initialized, do so
        if (!initialized_) {
            initGLFW();
        }

        ++refCount_;
        Logger::debug("GLFWManager: refCount incremented to {}", refCount_);
    }

    void GLFWManager::decrementRefCount() {

        std::lock_guard<std::mutex> lock(mutex_);

        --refCount_;
        Logger::debug("GLFWManager: refCount decremented to {}", refCount_);

    }

    void GLFWManager::initGLFW() {

        if (initialized_) {
            return;
        }

        Logger::debug("Initializing GLFW...");

        if (!glfwInit()) {

            Logger::error("Failed to initialize GLFW!");
            throw std::runtime_error("Failed to initialize GLFW!");
        }

        initialized_ = true;
        Logger::debug("GLFW initialized successfully.");
    }

    void GLFWManager::terminateGLFW() {

        if (!initialized_) {
            return;
        }

        Logger::debug("Terminating GLFW.");

        glfwTerminate();
        initialized_ = false;
    }

} // namespace Gem
