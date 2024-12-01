#include "../eventManager.h"

namespace Gem {
    namespace Core {

        EventManager::ListenerID EventManager::add_listener(const std::function<void(const SDL_Event&)>& listener) {
            std::lock_guard<std::mutex> lock(mutex_);
            ListenerID id = nextListenerID_++;
            listeners_[id] = listener;
            return id;
        }

        void EventManager::remove_listener(ListenerID id) {
            std::lock_guard<std::mutex> lock(mutex_);
            listeners_.erase(id);
        }

        void EventManager::dispatch_event(const SDL_Event& event) {
            std::lock_guard<std::mutex> lock(mutex_);
            for (const auto& [id, listener] : listeners_) {
                listener(event);
            }
        }

    } // namespace Core
} // namespace Gem
