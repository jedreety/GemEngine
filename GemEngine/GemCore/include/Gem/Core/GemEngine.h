#pragma once

#include <vulkan/vulkan.h>
#include <vector>
#include <stdexcept>

namespace Gem {

    /**
     * @class GemEngine
     * @brief Singleton class to manage Vulkan initialization and provide global access to the Vulkan instance.
     */
    class GemEngine {
    public:
        /**
         * @brief Gets the singleton instance of GemEngine.
         */
        static GemEngine& getInstance() noexcept {
            static GemEngine instance;
            return instance;
        }

        /**
         * @brief Initializes Vulkan (if not already initialized).
         */
        void init();

        /**
         * @brief Gets the Vulkan instance handle.
         */
        [[nodiscard]] VkInstance getInstanceHandle() const noexcept;

    private:
        GemEngine() = default;
        ~GemEngine();

        // Delete copy/move
        GemEngine(const GemEngine&) = delete;
        GemEngine& operator=(const GemEngine&) = delete;
        GemEngine(GemEngine&&) = delete;
        GemEngine& operator=(GemEngine&&) = delete;

    private:
        void createInstance();
        void setupDebugMessenger();
        bool checkValidationLayerSupport() const;

        std::vector<const char*> getRequiredExtensions() const;

    private:
        VkInstance instance_ = VK_NULL_HANDLE;

        VkDebugUtilsMessengerEXT debugMessenger_ = VK_NULL_HANDLE;
        bool enableValidationLayers_ = true;  // Toggle to enable/disable validation layers

        // Typically we’d have a list of desired validation layers
        const std::vector<const char*> validationLayers_ = {
            "VK_LAYER_KHRONOS_validation"
        };
    };

} // namespace Gem
