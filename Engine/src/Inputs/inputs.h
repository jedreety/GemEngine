#pragma once

#include <array>
#include <mutex>
#include <atomic>
#include <functional>
#include <vector>
#include <SDL2/SDL.h>
#include "Key.h"
#include "eventManager.h"

namespace Gem {
    namespace Input {

        /**
         * @brief Manages input states for keyboard keys and mouse buttons using SDL2.
         *
         * The Inputs class tracks the state of keyboard keys and mouse buttons,
         * including whether they are currently pressed, were pressed in the current frame,
         * or were released in the current frame. It also tracks mouse movement and scroll wheel input.
         * Users can register custom handlers for key and mouse button events.
         */
        class Inputs {
        public:

            /**
             * @brief Maximum number of keys and mouse buttons to handle.
             *
             * Calculated as the number of scancodes for keyboard keys and additional slots for mouse buttons.
             */
            static constexpr int MAX_KEYS = SDL_NUM_SCANCODES + 6; // 6 mouse buttons (1-5)

            /**
             * @brief Offset value used to map mouse button codes into the key array.
             *
             * Mouse buttons are mapped into this array by adding this offset to their codes.
             */
            static constexpr int MOUSE_BUTTON_OFFSET = SDL_NUM_SCANCODES;

            /**
             * @brief Constructs an Inputs object and initializes key states.
             *
             * @param eventManager Reference to the EventManager for registering event listeners.
             */
            Inputs(Core::EventManager& eventManager);

            /**
             * @brief Destructor that unregisters event listeners.
             */
            ~Inputs();

            /**
             * @brief Resets per-frame key and mouse button states and scroll delta.
             *
             * Should be called at the beginning or end of each frame to reset the temporary key states and scroll delta.
             */
            void update();

            // --- Key state queries ---

            [[nodiscard]] bool is_key_pressed(SDL_Scancode scancode) const noexcept;
            [[nodiscard]] bool was_key_pressed(SDL_Scancode scancode) const noexcept;
            [[nodiscard]] bool was_key_released(SDL_Scancode scancode) const noexcept;

            // --- Mouse button state queries ---

            [[nodiscard]] bool is_mouse_button_pressed(Uint8 button) const noexcept;
            [[nodiscard]] bool was_mouse_button_pressed(Uint8 button) const noexcept;
            [[nodiscard]] bool was_mouse_button_released(Uint8 button) const noexcept;

            // --- Mouse movement and scroll wheel input ---

            /**
             * @brief Gets the current mouse position.
             *
             * @param x Reference to store the x-coordinate.
             * @param y Reference to store the y-coordinate.
             */
            void get_mouse_position(int& x, int& y) const;

            /**
             * @brief Gets the scroll wheel delta since the last update.
             *
             * @param x Reference to store the horizontal scroll delta.
             * @param y Reference to store the vertical scroll delta.
             */
            void get_scroll_delta(int& x, int& y) const;

            // --- Event processing ---

            /**
             * @brief Processes an SDL event for input handling.
             *
             * Call this method for each SDL_Event to handle input events.
             *
             * @param event The SDL_Event to process.
             */
            void process_event(const SDL_Event& event);

            // --- Custom Input Handlers ---

            /**
             * @brief Adds a custom key event handler.
             *
             * @param handler A function that takes SDL_Scancode and action.
             */
            void add_key_handler(const std::function<void(SDL_Scancode, Uint8)>& handler);

            /**
             * @brief Adds a custom mouse button event handler.
             *
             * @param handler A function that takes Uint8 button and action.
             */
            void add_mouse_button_handler(const std::function<void(Uint8, Uint8)>& handler);

        private:

            // --- Internal event handlers ---

            void key_event(SDL_Scancode scancode, Uint8 action);
            void mouse_button_event(Uint8 button, Uint8 action);

            /**
             * @brief Array of Key objects representing the state of each key and mouse button.
             *
             * Keyboard keys and mouse buttons are stored in this array. Mouse buttons are mapped
             * into this array using the MOUSE_BUTTON_OFFSET.
             */
            std::array<Input::Key, MAX_KEYS> keys_;

            mutable std::mutex mutex_; ///< Mutex for thread safety.

            std::atomic<int> mouseX_; ///< Current mouse x-coordinate.
            std::atomic<int> mouseY_; ///< Current mouse y-coordinate.

            std::atomic<int> scrollX_; ///< Scroll wheel delta x since last update.
            std::atomic<int> scrollY_; ///< Scroll wheel delta y since last update.

            std::vector<std::function<void(SDL_Scancode, Uint8)>> keyHandlers_;
            std::vector<std::function<void(Uint8, Uint8)>> mouseButtonHandlers_;

            Core::EventManager& eventManager_; ///< Reference to the EventManager.
            Core::EventManager::ListenerID listenerID_; ///< ID of the registered event listener.
        };

    } // namespace Input
} // namespace Gem
