#include <Gem/Core/GemEngine.h>
#include <GLFW_Manager.h>
#include <Gem/Core/Logger.h>

#include <function_overload.h>

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
		running_ = true;
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

    bool GemEngine::isRunning() {

        std::lock_guard<std::mutex> lock(mutex_);
        return running_;
    }

    void GemEngine::exit() {
        
        std::lock_guard<std::mutex> lock(mutex_);
        
        if (running_) {
            shutdown(); // Clean up resources
            running_ = false; // Signal the engine to stop running
        }
    }


    bool GemEngine::initOpenGL() {

		Gem::GLFWManager::getInstance().initGLFW();
        
        Logger::debug("GemEngine: Initializing OpenGL...");

		Gem::GLFW::set_context_version(4, 6);
		Gem::GLFW::set_openGL_profile(GLFW_OPENGL_CORE_PROFILE);
        
        // Create temporary window for OpenGL context
        GLFWwindow* tempWindow = Gem::GLFW::create_window(1, 1, "Temp Window");
        if (!tempWindow) {
            Logger::error("Failed to create temporary GLFW window!");
            return false;
        }
        Gem::GLFW::make_context_current(tempWindow);

        // Initialize GLAD
        if (!Gem::GLAD::init()) {

            Logger::error("Failed to initialize GLAD!");
            glfwDestroyWindow(tempWindow);
            return false;
        }

        bool depth_test = true;
        bool cull_face = true;
        bool blending = true;
        bool multisampling = true;

        depth_test ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST);

        if (cull_face) {
            glEnable(GL_CULL_FACE);
            glCullFace(GL_BACK);
            glFrontFace(GL_CW);
        }
        else 
            glDisable(GL_CULL_FACE);

        if (blending) {
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        }
        else 
            glDisable(GL_BLEND);

        multisampling ? glEnable(GL_MULTISAMPLE) : glDisable(GL_MULTISAMPLE);

        // Cleanup temporary window
        Gem::GLFW::destroy_window(tempWindow);
        Logger::debug("GemEngine: OpenGL initialized successfully.");
        return true;
    }

} // namespace Gem