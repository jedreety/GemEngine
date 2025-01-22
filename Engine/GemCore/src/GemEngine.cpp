#include <Gem/Core/GemEngine.h>
#include <Gem/Core/GLFW_Manager.h>
#include <Gem/Core/Logger.h>

#include <GLFW/glfw3.h>  // for glfwGetRequiredInstanceExtensions
#include <cstring>       // for strcmp

namespace Gem {

    // Forward-declare function to create a DebugUtils messenger (if you want debug callbacks)
    static VkResult CreateDebugUtilsMessengerEXT(
        VkInstance instance,
        const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
        const VkAllocationCallbacks* pAllocator,
        VkDebugUtilsMessengerEXT* pDebugMessenger)
    {
        auto func = (PFN_vkCreateDebugUtilsMessengerEXT)
            vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
        if (func != nullptr) {
            return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
        }
        else {
            return VK_ERROR_EXTENSION_NOT_PRESENT;
        }
    }

    static void DestroyDebugUtilsMessengerEXT(
        VkInstance instance,
        VkDebugUtilsMessengerEXT debugMessenger,
        const VkAllocationCallbacks* pAllocator)
    {
        auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)
            vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
        if (func != nullptr) {
            func(instance, debugMessenger, pAllocator);
        }
    }

    void GemEngine::init() {
        if (instance_ != VK_NULL_HANDLE) {
            Logger::warning("GemEngine::init called, but Vulkan is already initialized.");
            return;
        }

		// Initialise GLFW
		GLFWManager::getInstance().initGLFW();

        Logger::debug("Initializing Vulkan...");
        createInstance();

        // Optional: Setup debug messenger if validation is enabled
        if (enableValidationLayers_) {
            setupDebugMessenger();
        }

        Logger::debug("Vulkan initialized successfully.");
    }

    GemEngine::~GemEngine() {
        if (debugMessenger_ != VK_NULL_HANDLE) {
            DestroyDebugUtilsMessengerEXT(instance_, debugMessenger_, nullptr);
        }

        if (instance_ != VK_NULL_HANDLE) {
            Logger::debug("Destroying Vulkan instance.");
            vkDestroyInstance(instance_, nullptr);
            instance_ = VK_NULL_HANDLE;
        }
    }

    VkInstance GemEngine::getInstanceHandle() const noexcept {
        return instance_;
    }

    void GemEngine::createInstance() {
        // Check validation layer support if enabled
        if (enableValidationLayers_ && !checkValidationLayerSupport()) {
            Logger::error("Validation layers requested, but not available!");
            throw std::runtime_error("Validation layers requested, but not available!");
        }

        auto extensions = getRequiredExtensions();

        // Vulkan application info
        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "GemEngine Application";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "GemEngine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_2;

        // Instance creation info
        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;
        createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
        createInfo.ppEnabledExtensionNames = extensions.data();

        // If validation is enabled, include them
        if (enableValidationLayers_) {
            createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers_.size());
            createInfo.ppEnabledLayerNames = validationLayers_.data();
        }
        else {
            createInfo.enabledLayerCount = 0;
            createInfo.ppEnabledLayerNames = nullptr;
        }

        // Setup a VkDebugUtilsMessengerCreateInfoEXT to pass in pNext
        // so we catch validation info even during vkCreateInstance and vkDestroyInstance
        VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
        if (enableValidationLayers_) {
            debugCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
            debugCreateInfo.messageSeverity =
                VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
                VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
                VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
            debugCreateInfo.messageType =
                VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
                VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
                VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
            debugCreateInfo.pfnUserCallback = [](VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                VkDebugUtilsMessageTypeFlagsEXT messageType,
                const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
                void* pUserData) -> VkBool32
                {
                    // Replace with your preferred logging level
                    if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT) {
                        Logger::warning("[VALIDATION LAYER] {}", pCallbackData->pMessage);
                    }
                    else if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT) {
                        Logger::error("[VALIDATION LAYER] {}", pCallbackData->pMessage);
                    }
                    else {
                        Logger::debug("[VALIDATION LAYER] {}", pCallbackData->pMessage);
                    }
                    return VK_FALSE;
                };
            createInfo.pNext = &debugCreateInfo;
        }

        // Create Vulkan instance
        VkResult result = vkCreateInstance(&createInfo, nullptr, &instance_);
        if (result != VK_SUCCESS) {
            Logger::error("Failed to create Vulkan instance (error code: {})", result);
            throw std::runtime_error("Failed to create Vulkan instance.");
        }
        Logger::debug("Vulkan instance created successfully.");
    }

    void GemEngine::setupDebugMessenger() {
        if (!enableValidationLayers_) return;

        // Create info for the debug messenger
        VkDebugUtilsMessengerCreateInfoEXT createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        createInfo.messageSeverity =
            VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
        createInfo.messageType =
            VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
        createInfo.pfnUserCallback = [](VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
            VkDebugUtilsMessageTypeFlagsEXT messageType,
            const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
            void* pUserData) -> VkBool32
            {
                if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT) {
                    Logger::warning("[VALIDATION LAYER] {}", pCallbackData->pMessage);
                }
                else if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT) {
                    Logger::error("[VALIDATION LAYER] {}", pCallbackData->pMessage);
                }
                else {
                    Logger::debug("[VALIDATION LAYER] {}", pCallbackData->pMessage);
                }
                return VK_FALSE;
            };

        if (CreateDebugUtilsMessengerEXT(instance_, &createInfo, nullptr, &debugMessenger_) != VK_SUCCESS) {
            Logger::warning("Failed to create debug messenger!");
        }
        else {
            Logger::debug("Debug messenger created successfully.");
        }
    }

    bool GemEngine::checkValidationLayerSupport() const {
        // Enumerate all available layers
        uint32_t layerCount;
        vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
        std::vector<VkLayerProperties> availableLayers(layerCount);
        vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

        // Check each requested layer against the list
        for (const char* layerName : validationLayers_) {
            bool layerFound = false;
            for (const auto& layerProperties : availableLayers) {
                if (strcmp(layerName, layerProperties.layerName) == 0) {
                    layerFound = true;
                    break;
                }
            }
            if (!layerFound) {
                return false;
            }
        }
        return true;
    }

    std::vector<const char*> GemEngine::getRequiredExtensions() const {
        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        if (!glfwExtensions || glfwExtensionCount == 0) {
            throw std::runtime_error("GLFW failed to provide required Vulkan instance extensions.");
        }

        // Copy them into a std::vector
        std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

        // If using validation layers, we also need the VK_EXT_debug_utils extension
        if (enableValidationLayers_) {
            extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
        }

        return extensions;
    }

} // namespace Gem
