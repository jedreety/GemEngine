#include <Key.h>

namespace Gem {
    namespace Input {

        Key::Key()
            : is_pressed_(false)
            , was_pressed_(false)
            , was_released_(false)
        {
            // Default initialization
        }

        void Key::update(bool pressed_now)
        {
            // If previously not pressed, but now pressed -> was_pressed_ = true
            was_pressed_ = (!is_pressed_ && pressed_now);
            // If previously pressed, but now not pressed -> was_released_ = true
            was_released_ = (is_pressed_ && !pressed_now);

            // Update the current state
            is_pressed_ = pressed_now;
        }

        void Key::reset()
        {
            // Reset the transitional states each frame
            was_pressed_ = false;
            was_released_ = false;
        }

        bool Key::is_pressed() const noexcept
        {
            return is_pressed_;
        }

        bool Key::was_pressed() const noexcept
        {
            return was_pressed_;
        }

        bool Key::was_released() const noexcept
        {
            return was_released_;
        }

    } // namespace Input
} // namespace Gem
