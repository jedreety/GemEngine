#pragma once

namespace Gem {
    namespace Input {

        /**
         * @brief Represents the state of a single key or mouse button.
         *
         * Tracks whether a key is currently pressed, was pressed in this frame,
         * or was released in this frame.
         */
        class Key
        {
        public:
            /**
             * @brief Default constructor initializes all states to false.
             */
            Key();

            /**
             * @brief Updates the key's state based on the new "pressed" value.
             *
             * @param pressed_now True if the key is currently pressed, false otherwise.
             */
            void update(bool pressed_now);

            /**
             * @brief Resets the per-frame states (was_pressed, was_released).
             *
             * Call this once per frame (e.g., after polling events).
             */
            void reset();

            /**
             * @brief Checks if the key is currently held down.
             */
            [[nodiscard]] bool is_pressed() const noexcept;

            /**
             * @brief Checks if the key was pressed during this frame.
             *
             * i.e., it transitioned from "not pressed" to "pressed."
             */
            [[nodiscard]] bool was_pressed() const noexcept;

            /**
             * @brief Checks if the key was released during this frame.
             *
             * i.e., it transitioned from "pressed" to "not pressed."
             */
            [[nodiscard]] bool was_released() const noexcept;

        private:
            bool is_pressed_ = false; ///< True if the key is currently pressed.
            bool was_pressed_ = false; ///< True if the key was pressed this frame.
            bool was_released_ = false; ///< True if the key was released this frame.
        };

    } // namespace Input
} // namespace Gem
