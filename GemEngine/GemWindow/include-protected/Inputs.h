#pragma once

#include <array>
#include "Key.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace Gem {
    namespace Input {

        /**
         * @brief Manages input states (keyboard + mouse).
         *
         * Tracks whether keys/mouse buttons are pressed, were pressed this frame,
         * or were released this frame.
         */
        class Inputs
        {
        public:
            /**
             * @brief The maximum index in `keys_`.
             *
             * We store keyboard keys [0..GLFW_KEY_LAST] and mouse buttons
             * [MOUSE_BUTTON_OFFSET.. MOUSE_BUTTON_OFFSET+GLFW_MOUSE_BUTTON_LAST].
             */
            static constexpr int MAX_KEYS = (GLFW_KEY_LAST + 1) + (GLFW_MOUSE_BUTTON_LAST + 1);

            /**
             * @brief Mouse buttons get an offset so they don't overlap with keyboard keys.
             */
            static constexpr int MOUSE_BUTTON_OFFSET = GLFW_KEY_LAST + 1;
            
            /** 
             * @brief Gets the singleton instance of the Inputs class.
             * @return Reference to the singleton Inputs instance.
             */
            static Inputs& getInstance();
            
            /**
             * @brief Deletes the copy constructor to prevent copying.
             */
            Inputs(const Inputs&) = delete;
            
            /**
             * @brief Assignment operator that returns a reference to the singleton instance.
             * 
             * This allows code like `inputs_ = Input::Inputs::getInstance()` to work
             * by returning a reference to the singleton rather than allowing actual assignment.
             * 
             * @return Reference to the singleton Inputs instance.
             */
            Inputs& operator=(const Inputs&);

            /**
             * @brief Process a keyboard event (key press/release).
             *
             * @param keyCode  The GLFW key code (e.g. GLFW_KEY_SPACE).
             * @param action   The GLFW action (GLFW_PRESS, GLFW_RELEASE, etc.).
             */
            void key_callback(int keyCode, int action);

            /**
             * @brief Process a mouse button event (mouse press/release).
             *
             * @param button  The GLFW mouse button code (e.g. GLFW_MOUSE_BUTTON_LEFT).
             * @param action  The GLFW action (GLFW_PRESS, GLFW_RELEASE, etc.).
             */
            void mouse_button_callback(int button, int action);

            /**
             * @brief Call once per frame to reset the transitional states (was_pressed, was_released).
             *
             * Typically called after `glfwPollEvents()` in the main loop.
             */
            void update();

            //-------------------------------------------------------------------------
            // Keyboard queries

            /**
             * @brief Returns true if a key is currently held down.
             *
             * @param keyCode  The GLFW key code.
             */
            [[nodiscard]] bool is_key_pressed(int keyCode) const noexcept;

            /**
             * @brief Returns true if a key was pressed this frame.
             *
             * @param keyCode  The GLFW key code.
             */
            [[nodiscard]] bool was_key_pressed(int keyCode) const noexcept;

            /**
             * @brief Returns true if a key was released this frame.
             *
             * @param keyCode  The GLFW key code.
             */
            [[nodiscard]] bool was_key_released(int keyCode) const noexcept;

            //-------------------------------------------------------------------------
            // Mouse queries

            /**
             * @brief Returns true if a mouse button is currently held down.
             *
             * @param button  The GLFW button code (e.g. GLFW_MOUSE_BUTTON_LEFT).
             */
            [[nodiscard]] bool is_mouse_button_pressed(int button) const noexcept;

            /**
             * @brief Returns true if a mouse button was pressed this frame.
             */
            [[nodiscard]] bool was_mouse_button_pressed(int button) const noexcept;

            /**
             * @brief Returns true if a mouse button was released this frame.
             */
            [[nodiscard]] bool was_mouse_button_released(int button) const noexcept;

        private:
            /**
             * @brief Private constructor to prevent direct instantiation.
             */
            Inputs();
            
            /**
             * @brief Internal array of `Key` objects representing keyboard + mouse.
             */
            std::array<Key, MAX_KEYS> keys_;
        };

    } // namespace Input
} // namespace Gem
