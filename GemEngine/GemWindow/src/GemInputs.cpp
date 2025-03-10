#include <Inputs.h>
#include <Gem/Core/Logger.h> // Use your logging system
#include <algorithm>         // for std::fill

namespace Gem {
    namespace Input {

        // Static method to get the singleton instance
        Inputs& Inputs::getInstance() {
            static Inputs instance;
            return instance;
        }
        
        // Private constructor
        Inputs::Inputs()
        {
            // Fill our array with default-constructed Key objects
            keys_.fill(Key());
        }

        // Assignment operator implementation
        Inputs& Inputs::operator=(const Inputs&) {
            // Return reference to the singleton instance
            return getInstance();
        }
        
        void Inputs::key_callback(int keyCode, int action)
        {
            // Range check for valid keyCode
            if (keyCode < 0 || keyCode > GLFW_KEY_LAST) {
                Gem::Logger::error("Inputs::key_callback: Invalid keyCode = {}", keyCode);
                return;
            }

            Gem::Logger::debug("Key event: key={}, action={}", keyCode, action);

            // Consider both GLFW_PRESS and GLFW_REPEAT as key being pressed
            // This ensures continuous movement when keys are held down
            bool pressed = (action != GLFW_RELEASE);
            keys_[keyCode].update(pressed);
        }

        void Inputs::mouse_button_callback(int button, int action)
        {
            int keyCode = button + MOUSE_BUTTON_OFFSET;
            if (keyCode < MOUSE_BUTTON_OFFSET || keyCode >= MAX_KEYS) {
                Gem::Logger::error("Inputs::mouse_button_callback: Invalid button = {}", button);
                return;
            }

            bool pressed = (action != GLFW_RELEASE);
            keys_[keyCode].update(pressed);
        }

        void Inputs::update()
        {
            // Reset transitional states of all keys once per frame
            for (auto& key : keys_) {
                key.reset();
            }
        }

        //--------------------------------------------------------------------------
        // Keyboard queries

        bool Inputs::is_key_pressed(int keyCode) const noexcept
        {
            if (keyCode < 0 || keyCode > GLFW_KEY_LAST) {
                Gem::Logger::error("Inputs::is_key_pressed: Invalid keyCode = {}", keyCode);
                return false;
            }
            return keys_[keyCode].is_pressed();
        }

        bool Inputs::was_key_pressed(int keyCode) const noexcept
        {
            if (keyCode < 0 || keyCode > GLFW_KEY_LAST) {
                Gem::Logger::error("Inputs::was_key_pressed: Invalid keyCode = {}", keyCode);
                return false;
            }
            return keys_[keyCode].was_pressed();
        }

        bool Inputs::was_key_released(int keyCode) const noexcept
        {
            if (keyCode < 0 || keyCode > GLFW_KEY_LAST) {
                Gem::Logger::error("Inputs::was_key_released: Invalid keyCode = {}", keyCode);
                return false;
            }
            return keys_[keyCode].was_released();
        }

        //--------------------------------------------------------------------------
        // Mouse queries

        bool Inputs::is_mouse_button_pressed(int button) const noexcept
        {
            int keyCode = button + MOUSE_BUTTON_OFFSET;
            if (keyCode < MOUSE_BUTTON_OFFSET || keyCode >= MAX_KEYS) {
                Gem::Logger::error("Inputs::is_mouse_button_pressed: Invalid button = {}", button);
                return false;
            }
            return keys_[keyCode].is_pressed();
        }

        bool Inputs::was_mouse_button_pressed(int button) const noexcept
        {
            int keyCode = button + MOUSE_BUTTON_OFFSET;
            if (keyCode < MOUSE_BUTTON_OFFSET || keyCode >= MAX_KEYS) {
                Gem::Logger::error("Inputs::was_mouse_button_pressed: Invalid button = {}", button);
                return false;
            }
            return keys_[keyCode].was_pressed();
        }

        bool Inputs::was_mouse_button_released(int button) const noexcept
        {
            int keyCode = button + MOUSE_BUTTON_OFFSET;
            if (keyCode < MOUSE_BUTTON_OFFSET || keyCode >= MAX_KEYS) {
                Gem::Logger::error("Inputs::was_mouse_button_released: Invalid button = {}", button);
                return false;
            }
            return keys_[keyCode].was_released();
        }

    } // namespace Input
} // namespace Gem
