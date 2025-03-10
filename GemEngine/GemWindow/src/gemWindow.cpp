#include <Gem/Window/Window.h>
#include <function_overload.h>
#include <GLFW_Manager.h>
#include <Gem/Core/Logger.h>
#include <stdexcept>

namespace Gem {

    Window::Window(int width, int height, const char* title)
        : window_(nullptr), title_(title), width_(width), height_(height), inputs_(Input::Inputs::getInstance()) {

        // Ensure GLFW is initialized (refCount incremented)
        GLFWManager::getInstance().incrementRefCount();

        initWindow();

        Gem::GLFW::make_context_current(window_);
		camera_ = new Gem::Graphics::Camera(glm::vec3(0, 0, 0), 60);
    }

    Window::~Window() {
        if (window_) {
            Gem::Logger::info("Destroying window: {}", title_);
            Gem::GLFW::destroy_window(window_);
            window_ = nullptr;
        }

        // Clean up the camera object to prevent memory leak
        if (camera_) {
            delete camera_;
            camera_ = nullptr;
        }

        // We don't need to delete inputs_ as it's now a reference to the singleton
        
        // Decrement GLFW refCount (possibly triggers glfwTerminate if this was the last window)
        GLFWManager::getInstance().decrementRefCount();
    }

    void Window::initWindow() {

        // Configure GLFW for OpenGL
        Gem::GLFW::window_hint(GLFW_CLIENT_API, GLFW_OPENGL_API);
        Gem::GLFW::window_hint(GLFW_RESIZABLE, GLFW_TRUE);

        // Create GLFW window
        window_ = Gem::GLFW::create_window(width_, height_, title_);
        if (!window_) {
            Gem::Logger::error("Failed to create GLFW window: {}", title_);
            throw std::runtime_error("Failed to create GLFW window!");
        }

        Gem::Logger::info("Window created: {} ({}x{})", title_, width_, height_);
        setCallbacks();
    }

    bool Window::shouldClose() noexcept {
        return Gem::GLFW::window_should_close(window_);
    }
    
    void Window::update() noexcept {
        // Update input and timing systems
        Gem::GL::clear_color(0.15f, 0.15f, 0.15f, 0.5f);
        Gem::GL::clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        camera_->update(window_, static_cast<float>(clock_.getDeltaTime()));
        inputs_.update();
        clock_.update();
    }
    
    void Window::render() noexcept {
        // Clear the screen
        
        // Render here (to be implemented by derived classes or render systems)
        
        // Swap front and back buffers
        Gem::GLFW::swap_buffers(window_);
        
        // Poll for and process events
        Gem::GLFW::poll_events();
    }

    GLFWwindow* Window::getGLFWwindow() const noexcept {
        return window_;
    }

    void Window::setFramebufferSizeCallback(std::function<void(GLFWwindow*, int, int)> callback) {
        userFramebufferSizeCallback_ = callback;
        Gem::Logger::debug("Custom framebuffer size callback set.");
    }

    void Window::setKeyCallback(std::function<void(GLFWwindow*, int, int, int, int)> callback) {
        userKeyCallback_ = callback;
        Gem::Logger::debug("Custom key callback set.");
    }

    void Window::setMouseButtonCallback(std::function<void(GLFWwindow*, int, int, int)> callback) {
        userMouseButtonCallback_ = callback;
        Gem::Logger::debug("Custom mouse button callback set.");
    }

    void Window::setTitle(const char* newTitle) {
        title_ = newTitle;
        Gem::GLFW::set_window_title(window_, newTitle);
    }

    void Window::resize(int newWidth, int newHeight) {
        width_ = newWidth;
        height_ = newHeight;
        Gem::GLFW::set_window_size(window_, newWidth, newHeight);
    }

    int Window::getWidth() const noexcept {
        return width_;
    }

    int Window::getHeight() const noexcept {
        return height_;
    }

    void Window::setCallbacks() {
        Gem::GLFW::set_window_user_pointer(window_, this);

        // Framebuffer size callback
        Gem::GLFW::set_framebuffer_size_callback(window_, [](GLFWwindow* window, int width, int height) {
            auto self = static_cast<Window*>(Gem::GLFW::get_window_user_pointer(window));
            if (!self) return;

            // Update internal width/height
            self->width_ = width;
            self->height_ = height;

            if (self->userFramebufferSizeCallback_) {
                self->userFramebufferSizeCallback_(window, width, height);
            }
            Gem::Logger::info("Framebuffer resized: {}x{}", width, height);
            });

        // Key callback
        Gem::GLFW::set_key_callback(window_, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
            auto self = static_cast<Window*>(Gem::GLFW::get_window_user_pointer(window));
            if (!self) return;

            self->inputs_.key_callback(key, action);

            if (self->userKeyCallback_) {
                self->userKeyCallback_(window, key, scancode, action, mods);
            }
            // Gem::Logger::debug("Key event: key={}, action={}", key, action);
            });

        // Mouse button callback
        Gem::GLFW::set_mouse_button_callback(window_, [](GLFWwindow* window, int button, int action, int mods) {
            auto self = static_cast<Window*>(Gem::GLFW::get_window_user_pointer(window));
            if (!self) return;

            self->inputs_.mouse_button_callback(button, action);

            if (self->userMouseButtonCallback_) {
                self->userMouseButtonCallback_(window, button, action, mods);
            }
            Gem::Logger::debug("Mouse button event: button={}, action={}", button, action);
            });
    }

} // namespace Gem
