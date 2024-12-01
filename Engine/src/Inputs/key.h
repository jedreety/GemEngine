#pragma once

namespace Gem {
    namespace Input {

        /**
         * @brief Represents the state of a key or mouse button.
         *
         * Tracks whether the key is currently pressed, was pressed this frame, or was released this frame.
         */
        class Key {
        public:
            /**
             * @brief Constructs a Key object with default state.
             */
            Key();

            /**
             * @brief Updates the key's state based on whether it is pressed.
             *
             * @param isPressed True if the key is currently pressed, false otherwise.
             */
            void update(bool isPressed);

            /**
             * @brief Resets the per-frame pressed and released states.
             */
            void reset();

            /**
             * @brief Checks if the key is currently pressed.
             *
             * @return True if the key is pressed, false otherwise.
             */
            bool is_pressed() const noexcept;

            /**
             * @brief Checks if the key was pressed this frame.
             *
             * @return True if the key was pressed this frame, false otherwise.
             */
            bool was_pressed() const noexcept;

            /**
             * @brief Checks if the key was released this frame.
             *
             * @return True if the key was released this frame, false otherwise.
             */
            bool was_released() const noexcept;

        private:
            bool pressed_;      ///< True if the key is currently pressed.
            bool wasPressed_;   ///< True if the key was pressed this frame.
            bool wasReleased_;  ///< True if the key was released this frame.
        };

    } // namespace Input
} // namespace Gem
