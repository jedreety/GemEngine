#include "../inputs.h"
#include "../../Core/logger.h"
#include <iostream>
namespace Gem {
    namespace Input {

        // Constructor
        Inputs::Inputs(Core::EventManager& eventManager)
            : mouseX_(0), mouseY_(0), scrollX_(0), scrollY_(0), eventManager_(eventManager) {
            // Initialize all key states
            keys_.fill(Input::Key());

            // Register as an event listener
            eventManager_.add_listener([this](const SDL_Event& event) {
                this->process_event(event);
            });
        }

        Inputs::~Inputs() {
            // Unregister the listener using the ListenerID
            eventManager_.remove_listener(listenerID_);
        }

        // Resets per-frame key and mouse button states and scroll delta
        void Inputs::update() {
            std::lock_guard<std::mutex> lock(mutex_);

            // Reset the temporary states for all keys and mouse buttons
            for (auto& key : keys_) {
                key.reset();
            }

            // Reset scroll delta
            scrollX_ = 0;
            scrollY_ = 0;
        }

        // --- Key state queries ---

        bool Inputs::is_key_pressed(SDL_Scancode scancode) const noexcept {
            if (scancode >= 0 && scancode < SDL_NUM_SCANCODES) {
                std::lock_guard<std::mutex> lock(mutex_);
                return keys_[scancode].is_pressed();
            } else {
                LOG_ERROR("Inputs::is_key_pressed: Invalid scancode ({0}).", static_cast<int>(scancode));
                return false;
            }
        }

        bool Inputs::was_key_pressed(SDL_Scancode scancode) const noexcept {
            if (scancode >= 0 && scancode < SDL_NUM_SCANCODES) {
                std::lock_guard<std::mutex> lock(mutex_);
                return keys_[scancode].was_pressed();
            } else {
                LOG_ERROR("Inputs::was_key_pressed: Invalid scancode ({0}).", static_cast<int>(scancode));
                return false;
            }
        }

        bool Inputs::was_key_released(SDL_Scancode scancode) const noexcept {
            if (scancode >= 0 && scancode < SDL_NUM_SCANCODES) {
                std::lock_guard<std::mutex> lock(mutex_);
                return keys_[scancode].was_released();
            } else {
                LOG_ERROR("Inputs::was_key_released: Invalid scancode ({0}).", static_cast<int>(scancode));
                return false;
            }
        }

        // --- Mouse button state queries ---

        bool Inputs::is_mouse_button_pressed(Uint8 button) const noexcept {
            int keyCode = button + MOUSE_BUTTON_OFFSET - 1;
            if (keyCode >= MOUSE_BUTTON_OFFSET && keyCode < MAX_KEYS) {
                std::lock_guard<std::mutex> lock(mutex_);
                return keys_[keyCode].is_pressed();
            } else {
                LOG_ERROR("Inputs::is_mouse_button_pressed: Invalid keyCode ({0}) for button ({1}).", keyCode, static_cast<int>(button));
                return false;
            }
        }

        bool Inputs::was_mouse_button_pressed(Uint8 button) const noexcept {
            int keyCode = button + MOUSE_BUTTON_OFFSET - 1;
            if (keyCode >= MOUSE_BUTTON_OFFSET && keyCode < MAX_KEYS) {
                std::lock_guard<std::mutex> lock(mutex_);
                return keys_[keyCode].was_pressed();
            } else {
                LOG_ERROR("Inputs::was_mouse_button_pressed: Invalid keyCode ({0}) for button ({1}).", keyCode, static_cast<int>(button));
                return false;
            }
        }

        bool Inputs::was_mouse_button_released(Uint8 button) const noexcept {
            int keyCode = button + MOUSE_BUTTON_OFFSET - 1;
            if (keyCode >= MOUSE_BUTTON_OFFSET && keyCode < MAX_KEYS) {
                std::lock_guard<std::mutex> lock(mutex_);
                return keys_[keyCode].was_released();
            } else {
                LOG_ERROR("Inputs::was_mouse_button_released: Invalid keyCode ({0}) for button ({1}).", keyCode, static_cast<int>(button));
                return false;
            }
        }

        // --- Mouse movement and scroll wheel input ---

        void Inputs::get_mouse_position(int& x, int& y) const {
            x = mouseX_.load();
            y = mouseY_.load();
        }

        void Inputs::get_scroll_delta(int& x, int& y) const {
            x = scrollX_.load();
            y = scrollY_.load();
        }

        // --- Event processing ---

        void Inputs::process_event(const SDL_Event& event) {

            switch (event.type) {
                case SDL_KEYDOWN:
                    key_event(event.key.keysym.scancode, event.key.state);
                    break;
                case SDL_KEYUP:
                    key_event(event.key.keysym.scancode, event.key.state);
                    break;

                case SDL_MOUSEBUTTONDOWN:
                case SDL_MOUSEBUTTONUP:
                    mouse_button_event(event.button.button, event.button.state);
                    break;

                case SDL_MOUSEMOTION:
                    mouseX_.store(event.motion.x);
                    mouseY_.store(event.motion.y);
                    break;

                case SDL_MOUSEWHEEL:
                    scrollX_.fetch_add(event.wheel.x);
                    scrollY_.fetch_add(event.wheel.y);
                    break;

                default:
                    break;
            }
        }

        // --- Custom Input Handlers ---

        void Inputs::add_key_handler(const std::function<void(SDL_Scancode, Uint8)>& handler) {
            std::lock_guard<std::mutex> lock(mutex_);
            keyHandlers_.push_back(handler);
        }

        void Inputs::add_mouse_button_handler(const std::function<void(Uint8, Uint8)>& handler) {
            std::lock_guard<std::mutex> lock(mutex_);
            mouseButtonHandlers_.push_back(handler);
        }

        // --- Internal event handlers ---

        void Inputs::key_event(SDL_Scancode scancode, Uint8 action) {
            if (scancode >= 0 && scancode < SDL_NUM_SCANCODES) {
                {
                    std::lock_guard<std::mutex> lock(mutex_);
                    bool pressed = (action != SDL_RELEASED);
                    
                    keys_[scancode].update(pressed);
                }

                // Call custom handlers
                for (const auto& handler : keyHandlers_) {
                    handler(scancode, action);
                }
            } else {
                LOG_ERROR("Inputs::key_event: Invalid scancode ({0}).", static_cast<int>(scancode));
            }
        }

        void Inputs::mouse_button_event(Uint8 button, Uint8 action) {
            int keyCode = button + MOUSE_BUTTON_OFFSET - 1; // SDL mouse buttons start from 1
            if (keyCode >= MOUSE_BUTTON_OFFSET && keyCode < MAX_KEYS) {
                {
                    std::lock_guard<std::mutex> lock(mutex_);
                    bool pressed = (action != SDL_RELEASED);
                    keys_[keyCode].update(pressed);
                }

                // Call custom handlers
                for (const auto& handler : mouseButtonHandlers_) {
                    handler(button, action);
                }
            } else {
                LOG_ERROR("Inputs::mouse_button_event: Invalid keyCode ({0}) for button ({1}).", keyCode, static_cast<int>(button));
            }
        }

    } // namespace Input
} // namespace Gem
