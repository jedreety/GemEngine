#pragma once

#include <functional>
#include "../../../include-protected/Inputs.h"
#include <Gem/Graphics/camera.h>
#include <Gem/Core/Clock.h>

namespace Gem {

    /**
     * @class Window
     * @brief A Vulkan-compatible window class for managing GLFW windows and input callbacks.
     *
     * Creates a window using GLFW. The constructor automatically increments the reference count
     * in GLFWManager, and the destructor decrements it.
     */
    class Window {
    public:
        /**
         * @brief Constructs a Window object with default parameters.
         *
         * @param width Window width in pixels.
         * @param height Window height in pixels.
         * @param title Window title.
         */
        explicit Window(int width = 800, int height = 600, const char* title = "GemEngine Window");

        /**
         * @brief Destructor that cleans up the GLFW window.
         */
        ~Window();

        /**
         * @brief Checks if the window should close.
         *
         * @return True if the window should close, false otherwise.
         */
        [[nodiscard]] bool shouldClose() noexcept;

        /**
         * @brief Updates the window state, input systems, and camera.
         * 
         * Should be called once per frame before rendering.
         */
        void update() noexcept;
        
        /**
         * @brief Renders the window content and swaps buffers.
         * 
         * Should be called once per frame after updating.
         */
        void render() noexcept;

        /**
         * @brief Sets a user-provided framebuffer size callback function.
         *
         * @param callback The user-provided callback function.
         */
        void setFramebufferSizeCallback(std::function<void(GLFWwindow*, int, int)> callback);

        /**
         * @brief Sets a user-provided key callback function.
         *
         * @param callback The user-provided callback function.
         */
        void setKeyCallback(std::function<void(GLFWwindow*, int, int, int, int)> callback);

        /**
         * @brief Sets a user-provided mouse button callback function.
         *
         * @param callback The user-provided callback function.
         */
        void setMouseButtonCallback(std::function<void(GLFWwindow*, int, int, int)> callback);

        /**
         * @brief Allows the engine to update the window title at runtime.
         *
         * @param newTitle The new title string.
         */
        void setTitle(const char* newTitle);

        /**
         * @brief Programmatically resize the window (calls glfwSetWindowSize).
         *
         * @param newWidth  New width in pixels.
         * @param newHeight New height in pixels.
         */
        void resize(int newWidth, int newHeight);

        /**
         * @brief Gets the current width of the window.
         */
        [[nodiscard]] int getWidth() const noexcept;

        /**
         * @brief Gets the current height of the window.
         */
        [[nodiscard]] int getHeight() const noexcept;
    
    private:
        /**
         * @brief Initializes the GLFW window with Vulkan hints.
         */
        void initWindow();

        /**
         * @brief Sets GLFW callbacks for the window.
         */
        void setCallbacks();

        /**
         * @brief Gets the pointer to the GLFW window.
         *
         * @return Pointer to the GLFW window.
         */
        [[nodiscard]] GLFWwindow* getGLFWwindow() const noexcept;

    private:
        GLFWwindow* window_ = nullptr; ///< Pointer to the GLFW window.

		Gem::Input::Inputs& inputs_; ///< Reference to the Inputs singleton.
		Gem::Graphics::Camera* camera_; ///< Camera object for rendering.
		Gem::Clock clock_; ///< Clock object for timing.

        const char* title_;            ///< Window title.
        int width_;                    ///< Window width in pixels.
        int height_;                   ///< Window height in pixels.

        // User-provided callbacks
        std::function<void(GLFWwindow*, int, int)> userFramebufferSizeCallback_;
        std::function<void(GLFWwindow*, int, int, int, int)> userKeyCallback_;
        std::function<void(GLFWwindow*, int, int, int)> userMouseButtonCallback_;
    };

} // namespace Gem
