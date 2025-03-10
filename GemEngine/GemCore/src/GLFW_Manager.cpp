#include <GLFW_Manager.h>
#include <function_overload.h>
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

        // If reference count reaches zero, terminate GLFW
        if (refCount_ <= 0) {
            terminateGLFW();
        }
    }

    void GLFWManager::initGLFW() {

        if (initialized_) {
            return;
        }

        Logger::debug("Initializing GLFW...");

        if (!Gem::GLFW::init()) {

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

		Gem::GLFW::terminate();
        initialized_ = false;
    }

} // namespace Gem
