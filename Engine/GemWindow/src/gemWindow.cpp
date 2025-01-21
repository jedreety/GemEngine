#include <Gem/Window/Window.h>
#include <Gem/Core/GLFW_Manager.h>
#include <Gem/Core/Logger.h>
#include <stdexcept>

namespace Gem {

    Window::Window(int width, int height, const char* title)
        : window_(nullptr), title_(title), width_(width), height_(height) {

        // Ensure GLFW is initialized (refCount incremented)
        GLFWManager::getInstance().incrementRefCount();

        initWindow();
    }

    Window::~Window() {
        if (window_) {
            Gem::Logger::info("Destroying window: {}", title_);
            glfwDestroyWindow(window_);
            window_ = nullptr;
        }

        // Decrement GLFW refCount (possibly triggers glfwTerminate if this was the last window)
        GLFWManager::getInstance().decrementRefCount();
    }

    void Window::initWindow() {
        // Configure GLFW for Vulkan
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

        // Create GLFW window
        window_ = glfwCreateWindow(width_, height_, title_, nullptr, nullptr);
        if (!window_) {
            Gem::Logger::error("Failed to create GLFW window: {}", title_);
            throw std::runtime_error("Failed to create GLFW window!");
        }

        Gem::Logger::info("Window created: {} ({}x{})", title_, width_, height_);
        setCallbacks();
    }

    bool Window::shouldClose() const noexcept {
        return glfwWindowShouldClose(window_);
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

    void Window::setInputs(Gem::Input::Inputs* inputs) {
        inputs_ = inputs;
    }

    void Window::setTitle(const char* newTitle) {
        title_ = newTitle;
        glfwSetWindowTitle(window_, newTitle);
    }

    void Window::resize(int newWidth, int newHeight) {
        width_ = newWidth;
        height_ = newHeight;
        glfwSetWindowSize(window_, newWidth, newHeight);
    }

    int Window::getWidth() const noexcept {
        return width_;
    }

    int Window::getHeight() const noexcept {
        return height_;
    }

    void Window::setCallbacks() {
        glfwSetWindowUserPointer(window_, this);

        // Framebuffer size callback
        glfwSetFramebufferSizeCallback(window_, [](GLFWwindow* window, int width, int height) {
            auto self = static_cast<Window*>(glfwGetWindowUserPointer(window));
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
        glfwSetKeyCallback(window_, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
            auto self = static_cast<Window*>(glfwGetWindowUserPointer(window));
            if (!self) return;

            if (self->inputs_) {
                self->inputs_->key_callback(key, action);
            }

            if (self->userKeyCallback_) {
                self->userKeyCallback_(window, key, scancode, action, mods);
            }
            Gem::Logger::debug("Key event: key={}, action={}", key, action);
            });

        // Mouse button callback
        glfwSetMouseButtonCallback(window_, [](GLFWwindow* window, int button, int action, int mods) {
            auto self = static_cast<Window*>(glfwGetWindowUserPointer(window));
            if (!self) return;

            if (self->inputs_) {
                self->inputs_->mouse_button_callback(button, action);
            }

            if (self->userMouseButtonCallback_) {
                self->userMouseButtonCallback_(window, button, action, mods);
            }
            Gem::Logger::debug("Mouse button event: button={}, action={}", button, action);
            });
    }

} // namespace Gem
