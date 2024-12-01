#pragma once

// Include SDL for window management and Vulkan integration
#include <SDL2/SDL.h>
#include <SDL2/SDL_vulkan.h>

// Include Vulkan headers for Vulkan API functions and types
#include <vulkan/vulkan.h>

// Include standard library headers for thread safety and utility functions
#include <mutex>
#include <vector>
#include <stdexcept>
#include "logger.h"

namespace Gem {

    namespace Core {

        /**
         * @class GemInstance
         * @brief Manages the initialization and lifecycle of the Vulkan instance within the Gem Engine.
         *
         * The GemInstance class is implemented as a singleton to ensure that only one Vulkan instance
         * and SDL setup exists throughout the engine's lifecycle. It provides thread-safe access
         * to the Vulkan instance and ensures proper initialization and cleanup of resources.
         */
        class GemInstance {
        public:
            /**
             * @brief Retrieves the singleton instance of GemInstance.
             *
             * This static method ensures that only one instance of GemInstance exists.
             * It is thread-safe and lazily initializes the instance upon first access.
             *
             * @return Reference to the singleton GemInstance.
             */
            static GemInstance& getInstance();

            /**
             * @brief Initializes SDL and creates the Vulkan instance.
             *
             * This method performs the following steps:
             * 1. Initializes the SDL video subsystem.
             * 2. Loads the Vulkan library through SDL.
             * 3. Creates the Vulkan instance with the necessary extensions.
             *
             * @throws std::runtime_error if SDL initialization, Vulkan library loading,
             *         or Vulkan instance creation fails.
             */
            void initialize();

            /**
             * @brief Retrieves the Vulkan instance.
             *
             * Provides thread-safe access to the Vulkan instance.
             * Verifies that the instance has been initialized before returning it.
             *
             * @return VkInstance The Vulkan instance handle.
             * @throws std::runtime_error if the Vulkan instance is not initialized.
             */
            [[nodiscard]] VkInstance getVkInstance();

            /**
             * @brief Checks if the Vulkan instance has been initialized.
             *
             * @return true if the instance is initialized; false otherwise.
             */
            [[nodiscard]] bool isInitialized() const noexcept;

            // Delete copy constructor and assignment operator to prevent copying
            GemInstance(const GemInstance&) = delete;
            GemInstance& operator=(const GemInstance&) = delete;

        private:
            /**
             * @brief Constructs a new GemInstance object.
             *
             * Private constructor to enforce singleton pattern.
             * Initializes member variables but does not perform any initialization logic.
             */
            GemInstance();

            /**
             * @brief Destroys the GemInstance object.
             *
             * Cleans up Vulkan and SDL resources if they were initialized.
             * Ensures that all resources are properly released to prevent memory leaks.
             */
            ~GemInstance();

            /**
             * @brief Creates the Vulkan instance with required extensions.
             *
             * This helper function sets up the Vulkan application information,
             * specifies the necessary instance extensions, and creates the Vulkan instance.
             *
             * @throws std::runtime_error if Vulkan instance creation fails.
             */
            void createInstance();

        private:
            VkInstance instance;                 ///< Vulkan instance handle.
            bool initialized;                    ///< Flag indicating whether initialization has occurred.
            mutable std::mutex initMutex;        ///< Mutex to ensure thread-safe initialization and access.
        };
        
    } // namespace Core
} // namespace Gem