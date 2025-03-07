#include <Gem/Core/GemEngine.h>
#include <GLFW_Manager.h>
#include <Gem/Core/Logger.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdexcept>

namespace Gem {

    GemEngine& GemEngine::getInstance() {

        static GemEngine instance;
        return instance;
    }

    bool GemEngine::init() {

        std::lock_guard<std::mutex> lock(mutex_);
        
        // If already initialized, skip initialization
        if (initialized_) {
            Logger::debug("GemEngine: Already initialized, skipping initialization.");
            return true;
        }

        Logger::debug("GemEngine: Initializing...");


        // Initialize OpenGL
        if (!initOpenGL()) {
            Logger::error("GemEngine: Failed to initialize OpenGL!");
            return false;
        }

        initialized_ = true;
        Logger::debug("GemEngine: Initialized successfully.");

        return true;
    }

    void GemEngine::shutdown() {

        std::lock_guard<std::mutex> lock(mutex_);
        
        if (!initialized_) {
            Logger::debug("GemEngine: Not initialized, nothing to shut down.");
            return;
        }

        Logger::debug("GemEngine: Shutdown requested.");

        initialized_ = false;
   
        Logger::debug("GemEngine: Shut down completely.");
        
		Gem::GLFWManager::getInstance().terminateGLFW();
    }

    bool GemEngine::isInitialized() const {
        return initialized_;
    }

    bool GemEngine::initOpenGL() {
        // This assumes GLFW has been initialized and a context has been created
        // In a real implementation, you might want to create a temporary window for context
        // or handle this differently depending on your architecture
        
        // For now, we'll assume the context is created elsewhere before calling this
        // This is just a placeholder for actual OpenGL initialization

		Gem::GLFWManager::getInstance().initGLFW();
        
        Logger::debug("GemEngine: Initializing OpenGL...");
        
        // In a real implementation, you would initialize GLAD or another OpenGL loader here
        // For example:
        
        // Create temporary window for OpenGL context
        GLFWwindow* tempWindow = glfwCreateWindow(1, 1, "Temp Window", nullptr, nullptr);
        if (!tempWindow) {
            Logger::error("Failed to create temporary GLFW window!");
            return false;
        }
        glfwMakeContextCurrent(tempWindow);

        // Initialize GLAD
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            Logger::error("Failed to initialize GLAD!");
            glfwDestroyWindow(tempWindow);
            return false;
        }

        // Cleanup temporary window
        glfwDestroyWindow(tempWindow);
        Logger::debug("GemEngine: OpenGL initialized successfully.");
        return true;
    }

} // namespace Gem