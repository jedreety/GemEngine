#include "../key.h"

namespace Gem {
    namespace Input {

        Key::Key()
            : pressed_(false), wasPressed_(false), wasReleased_(false) {
        }

        void Key::update(bool isPressed) {
            if (isPressed != pressed_) {
                if (isPressed) {
                    wasPressed_ = true;
                } else {
                    wasReleased_ = true;
                }
                pressed_ = isPressed;
            }
        }

        void Key::reset() {
            wasPressed_ = false;
            wasReleased_ = false;
        }

        bool Key::is_pressed() const noexcept {
            return pressed_;
        }

        bool Key::was_pressed() const noexcept {
            return wasPressed_;
        }

        bool Key::was_released() const noexcept {
            return wasReleased_;
        }

    } // namespace Input
} // namespace Gem
