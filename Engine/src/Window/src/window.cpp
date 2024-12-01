#include "../window.h"
#include <stdexcept>
#include <vector>
#include <cstring>

namespace Gem {
    namespace Window {

        // Constructor
        Window::Window(int width, int height, const char* title)
            : width_(width), height_(height), title_(title) {

            init();
        }

        // Destructor
        Window::~Window() {
            // Clean up Vulkan surface
            cleanup_vulkan_surface();

            // Destroy the SDL window
            if (window_ != nullptr) {
                SDL_DestroyWindow(window_);
                window_ = nullptr;
            }

            // inputs_ is automatically cleaned up by unique_ptr
        }

        // Initialize the window and Vulkan surface
        void Window::init() {

            if (!are_attributes_set()) {
                LOG_ERROR("Window::init: Window attributes not properly set before initialization.");
                throw std::runtime_error("Window attributes not set.");
            }

            // Check if GemInstance is initialized
            Gem::Core::GemInstance& gemInstance = Gem::Core::GemInstance::getInstance();
            if (!gemInstance.isInitialized()) {
                LOG_ERROR("Window::init: GemInstance is not initialized. Please initialize it before creating a Window.");
                throw std::runtime_error("GemInstance not initialized");
            }

            // Create the SDL window
            create_window();

            // Create Vulkan surface
            create_vulkan_surface();

            // Initialize Inputs object with EventManager
            inputs_ = std::make_unique<Input::Inputs>(eventManager_);
        }

        // Check if attributes are set
        [[nodiscard]] bool Window::are_attributes_set() const noexcept {
            return width_ > 0 && height_ > 0 && title_ != nullptr;
        }

        // Create the SDL window
        void Window::create_window() {

            // Create SDL window with Vulkan support
            window_ = SDL_CreateWindow(
                title_,                      // Window title
                SDL_WINDOWPOS_CENTERED,      // X position
                SDL_WINDOWPOS_CENTERED,      // Y position
                width_,                      // Width in pixels
                height_,                     // Height in pixels
                SDL_WINDOW_VULKAN |          // Vulkan support flag
                SDL_WINDOW_RESIZABLE         // Allow window resizing
            );

            if (window_ == nullptr) {
                LOG_ERROR("Window::create_window: Failed to create SDL window: {0}", SDL_GetError());
                throw std::runtime_error("Failed to create SDL window");
            }
        }

        // Create Vulkan surface
        void Window::create_vulkan_surface() {

            // Get Vulkan instance from GemInstance
            VkInstance instance = Gem::Core::GemInstance::getInstance().getVkInstance();

            // Create Vulkan surface associated with the SDL window
            if (!SDL_Vulkan_CreateSurface(window_, instance, &surface_)) {
                LOG_ERROR("Window::create_vulkan_surface: Failed to create Vulkan surface: {0}", SDL_GetError());
                throw std::runtime_error("Failed to create Vulkan surface");
            }
        }

        // Clean up Vulkan surface
        void Window::cleanup_vulkan_surface() {

            // Get Vulkan instance from GemInstance
            VkInstance instance = Gem::Core::GemInstance::getInstance().getVkInstance();

            // Destroy Vulkan surface
            if (surface_ != VK_NULL_HANDLE) {
                vkDestroySurfaceKHR(instance, surface_, nullptr);
                surface_ = VK_NULL_HANDLE;
            }
        }

        // Handle SDL events
        void Window::handle_events() {

            SDL_Event event;
            while (SDL_PollEvent(&event)) {

                // Dispatch the event to all listeners
                eventManager_.dispatch_event(event);

                switch (event.type) {

                    case SDL_QUIT:
                        // User requests quit
                        should_close_ = true;
                        break;

                    case SDL_WINDOWEVENT:
                        if (event.window.event == SDL_WINDOWEVENT_CLOSE) {
                            // Window is being closed
                            should_close_ = true;
                        }
                        else if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
                            // Window has been resized
                            width_ = event.window.data1;
                            height_ = event.window.data2;

                            // Handle window resize in Vulkan (e.g., recreate swap chain)
                            // Set a flag or call a function to handle this
                        }
                        break;

                    default:
                        break;
                }
            }
        }

        // Checks if the window should close
        [[nodiscard]] bool Window::should_close() const noexcept {
            return should_close_;
        }

        // Gets the window width
        [[nodiscard]] int Window::get_width() const noexcept {
            return width_;
        }

        // Gets the window height
        [[nodiscard]] int Window::get_height() const noexcept {
            return height_;
        }

        // Gets the pointer to the SDL window
        [[nodiscard]] SDL_Window* Window::get_window_ptr() const noexcept {
            return window_;
        }

        // Gets the Vulkan surface handle
        [[nodiscard]] VkSurfaceKHR Window::get_surface() const noexcept {
            return surface_;
        }

        // Gets the pointer to the Inputs object
        [[nodiscard]] Input::Inputs* Window::get_inputs() const noexcept {
            return inputs_.get();
        }

        // Gets the EventManager instance
        Core::EventManager& Window::get_event_manager() {
            return eventManager_;
        }

        // Equality operator
        bool Window::operator==(const Window& other) const noexcept {
            return window_ == other.window_;
        }

        // Inequality operator
        bool Window::operator!=(const Window& other) const noexcept {
            return !(*this == other);
        }

    } // namespace Window
} // namespace Gem
