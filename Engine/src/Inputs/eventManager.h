#pragma once

#include <functional>
#include <vector>
#include <mutex>
#include <SDL2/SDL.h>
#include <unordered_map>
#include <atomic>

namespace Gem {
    namespace Core {

        /**
         * @brief Manages event listeners and dispatches SDL events to them.
         *
         * The EventManager allows different parts of the application to subscribe to SDL events.
         * It handles threading concerns and ensures that events are dispatched safely.
         */
        class EventManager {
        public:
            using ListenerID = uint64_t;

            /**
             * @brief Adds an event listener callback.
             *
             * @param listener A function that takes an `SDL_Event` reference.
             * @return A ListenerID that can be used to remove the listener.
             */
            ListenerID add_listener(const std::function<void(const SDL_Event&)>& listener);

            /**
             * @brief Removes an event listener callback.
             *
             * @param id The ListenerID of the listener to remove.
             */
            void remove_listener(ListenerID id);

            /**
             * @brief Dispatches an event to all registered listeners.
             *
             * @param event The SDL_Event to dispatch.
             */
            void dispatch_event(const SDL_Event& event);

        private:
            std::unordered_map<ListenerID, std::function<void(const SDL_Event&)>> listeners_;
            std::mutex mutex_;
            std::atomic<ListenerID> nextListenerID_{0};
        };

    } // namespace Core
} // namespace Gem
