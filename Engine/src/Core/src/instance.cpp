#include "../instance.h"

// Include platform-specific Vulkan headers
#if defined(_WIN32)
    #include <vulkan/vulkan_win32.h>
#elif defined(__APPLE__)
    #include <vulkan/vulkan_metal.h>
#elif defined(__linux__)
    #include <vulkan/vulkan_xcb.h> // For VK_KHR_XCB_SURFACE_EXTENSION_NAME
    // #include <vulkan/vulkan_xlib.h> // Uncomment if using Xlib
    // #include <vulkan/vulkan_wayland.h> // Uncomment if using Wayland
#endif
namespace Gem {

    namespace Core {

        // Initialize static variables for singleton
        GemInstance& GemInstance::getInstance() {
            static GemInstance instance;
            return instance;
        }

        GemInstance::GemInstance()
            : instance(VK_NULL_HANDLE), initialized(false) {
        }

        GemInstance::~GemInstance() {
            std::lock_guard<std::mutex> lock(initMutex);

            // Clean up Vulkan instance if initialized
            if (initialized && instance != VK_NULL_HANDLE) {
                vkDestroyInstance(instance, nullptr);
            }

            // Unload Vulkan library from SDL and quit SDL
            SDL_Vulkan_UnloadLibrary();

            SDL_Quit();
        }

        void GemInstance::initialize() {

            std::lock_guard<std::mutex> lock(initMutex);

            // Check if already initialized
            if (initialized) {
                return;
            }

            Gem::Core::Logger::init();

            // Initialize SDL without creating a window
            if (SDL_Init(SDL_INIT_VIDEO) != 0) {
                LOG_ERROR("Failed to initialize SDL2: {0}", SDL_GetError());
                throw std::runtime_error("Failed to initialize SDL2");
            }

            // Load the Vulkan library into SDL
            if (SDL_Vulkan_LoadLibrary(nullptr) != 0) {
                SDL_Quit();
                LOG_ERROR("Failed to load Vulkan library in SDL: {0}", SDL_GetError());
                throw std::runtime_error("Failed to load Vulkan library in SDL");
            }

            // Create the Vulkan instance
            createInstance();

            // Set the initialization flag
            initialized = true;
        }

        VkInstance GemInstance::getVkInstance() {
            std::lock_guard<std::mutex> lock(initMutex);

            // Verify if initialized before returning the instance
            if (!initialized || instance == VK_NULL_HANDLE) {
                LOG_ERROR("Vulkan instance is not initialized");
                throw std::runtime_error("Vulkan instance is not initialized");
            }

            return instance;
        }

        bool GemInstance::isInitialized() const noexcept {
            std::lock_guard<std::mutex> lock(initMutex);
            return initialized;
        }

        void GemInstance::createInstance() {
            // Manually specify the required Vulkan instance extensions
            std::vector<const char*> extensions;

            // Add the generic surface extension
            extensions.push_back(VK_KHR_SURFACE_EXTENSION_NAME);

            // Add platform-specific surface extensions
            #if defined(_WIN32)
                extensions.push_back(VK_KHR_WIN32_SURFACE_EXTENSION_NAME);
            #elif defined(__APPLE__)
                extensions.push_back("VK_EXT_metal_surface");
            #elif defined(__linux__)
                // Depending on your windowing system, uncomment the appropriate extension

                // For XCB:
                extensions.push_back(VK_KHR_XCB_SURFACE_EXTENSION_NAME);

                // For Xlib:
                // extensions.push_back(VK_KHR_XLIB_SURFACE_EXTENSION_NAME);

                // For Wayland:
                // extensions.push_back(VK_KHR_WAYLAND_SURFACE_EXTENSION_NAME);
            #endif

            // Set up Vulkan application information
            VkApplicationInfo appInfo{};
            appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
            appInfo.pApplicationName = "Vulkan SDL2 Engine";
            appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
            appInfo.pEngineName = "Gem Engine";
            appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
            appInfo.apiVersion = VK_API_VERSION_1_0;

            // Set up Vulkan instance creation information
            VkInstanceCreateInfo createInfo{};
            createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
            createInfo.pApplicationInfo = &appInfo;

            // Specify the extensions we need
            createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
            createInfo.ppEnabledExtensionNames = extensions.data();

            // Specify validation layers if needed (optional)
        #ifndef NDEBUG
            const std::vector<const char*> validationLayers = {
                "VK_LAYER_KHRONOS_validation"
            };

            // Check if validation layers are available (optional step)
            uint32_t layerCount;
            vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
            std::vector<VkLayerProperties> availableLayers(layerCount);
            vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

            bool layersAvailable = true;
            for (const char* layerName : validationLayers) {
                bool layerFound = false;
                for (const auto& layerProperties : availableLayers) {
                    if (strcmp(layerName, layerProperties.layerName) == 0) {
                        layerFound = true;
                        break;
                    }
                }
                if (!layerFound) {
                    layersAvailable = false;
                    break;
                }
            }

            if (layersAvailable) {
                createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
                createInfo.ppEnabledLayerNames = validationLayers.data();
            } else {
                // Validation layers not available, handle accordingly
                createInfo.enabledLayerCount = 0;
            }
        #else
            createInfo.enabledLayerCount = 0;
        #endif

            // Create the Vulkan instance
            if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
                SDL_Vulkan_UnloadLibrary();
                SDL_Quit();
                LOG_ERROR("Failed to create Vulkan instance");
                throw std::runtime_error("Failed to create Vulkan instance");
            }
        }

    } // namespace Core
} // namespace Gem