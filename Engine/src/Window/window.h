#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_vulkan.h>
#include <vulkan/vulkan.h>
#include <iostream>
#include <functional>
#include <memory>
#include "../Inputs/inputs.h" // Include your Inputs class
#include "../Inputs/eventManager.h"
#include "../Core/logger.h"
#include "../Core/instance.h" // Include GemInstance to access the Vulkan instance

namespace Gem {
    namespace Window {

        /**
         * @brief Window class for managing the SDL window and Vulkan surface.
         *
         * The Window class encapsulates the creation and management of an SDL window,
         * including Vulkan surface creation, event handling, and input management.
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
            Window(int width = 800, int height = 600, const char* title = "Default window name");

            /**
             * @brief Destructor that cleans up the SDL window and Vulkan surface.
             */
            ~Window();

            /**
             * @brief Checks if the window attributes are set.
             *
             * @return True if attributes are set, false otherwise.
             */
            [[nodiscard]] bool are_attributes_set() const noexcept;

            /**
             * @brief Handles SDL events.
             *
             * Polls and processes SDL events, including input events.
             */
            void handle_events();

            /**
             * @brief Checks if the window should close.
             *
             * @return True if the window should close, false otherwise.
             */
            [[nodiscard]] bool should_close() const noexcept;

            /**
             * @brief Gets the window width.
             *
             * @return Window width in pixels.
             */
            [[nodiscard]] int get_width() const noexcept;

            /**
             * @brief Gets the window height.
             *
             * @return Window height in pixels.
             */
            [[nodiscard]] int get_height() const noexcept;

            /**
             * @brief Gets the pointer to the SDL window.
             *
             * @return Pointer to the SDL window.
             */
            [[nodiscard]] SDL_Window* get_window_ptr() const noexcept;

            /**
             * @brief Gets the Vulkan surface associated with the window.
             *
             * @return Vulkan surface handle.
             */
            [[nodiscard]] VkSurfaceKHR get_surface() const noexcept;

            /**
             * @brief Gets the pointer to the Inputs object.
             *
             * @return Pointer to the Inputs object.
             */
            [[nodiscard]] Input::Inputs* get_inputs() const noexcept;

            /**
             * @brief Gets the EventManager instance.
             *
             * @return Reference to the EventManager.
             */
            Core::EventManager& get_event_manager();

            /**
             * @brief Equality operator.
             *
             * Compares two Window objects based on their SDL window pointers.
             *
             * @param other The other Window object to compare with.
             * @return True if both have the same SDL window pointer, false otherwise.
             */
            bool operator==(const Window& other) const noexcept;

            /**
             * @brief Inequality operator.
             *
             * Compares two Window objects based on their SDL window pointers.
             *
             * @param other The other Window object to compare with.
             * @return True if they have different SDL window pointers, false otherwise.
             */
            bool operator!=(const Window& other) const noexcept;

        private:

            /**
             * @brief Initializes the window and Vulkan surface.
             *
             * Creates the SDL window and Vulkan surface.
             *
             * @throws std::runtime_error if required attributes are not set or initialization fails.
             */
            void init();

            /**
             * @brief Creates the SDL window.
             *
             * @throws std::runtime_error if window creation fails.
             */
            void create_window();

            /**
             * @brief Creates the Vulkan surface.
             *
             * @throws std::runtime_error if Vulkan surface creation fails.
             */
            void create_vulkan_surface();

            /**
             * @brief Cleans up Vulkan surface.
             */
            void cleanup_vulkan_surface();

        private:

            SDL_Window* window_ = nullptr;         ///< Pointer to the SDL window.
            const char* title_;                    ///< Window title.
            int width_;                            ///< Window width in pixels.
            int height_;                           ///< Window height in pixels.
            bool should_close_ = false;            ///< Flag indicating whether the window should close.

            VkSurfaceKHR surface_ = VK_NULL_HANDLE;///< Vulkan surface handle.

            std::unique_ptr<Input::Inputs> inputs_; ///< Unique pointer to the Inputs object.

            Core::EventManager eventManager_; ///< EventManager instance.

            // Camera-related code is commented out as per your request.
            // Graphics::Camera* camera_ = nullptr;   ///< Pointer to the associated Camera object.
        };

    } // namespace Window
} // namespace Gem
