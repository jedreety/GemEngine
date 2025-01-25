project "GemEngine"
   kind "StaticLib"
   language "C++"
   cppdialect "C++20"
   targetdir "Build/%{cfg.buildcfg}"
   staticruntime "off"

   files { 
    "GemCore/include/Gem/Core/**.h", 
    "GemCore/src/**.cpp",
    
    "GemInput/include/Gem/Input/**.h", 
    "GemInput/src/**.cpp",
    
    "GemWindow/include/Gem/Window/**.h", 
    "GemWindow/src/**.cpp",
}

   includedirs
   {
      "GemCore/include",
      "GemInput/include",
      "GemWindow/include",
      "C:/glfw-3.4/include",
      "C:/VulkanSDK/1.3.296.0/Include",
      "C:/glm-1.0.1/glm"
   }

   libdirs {
    "C:/glfw-3.4/build/src/Debug",
    "C:/VulkanSDK/1.3.296.0/Lib"
    }

   links {

    "glfw3",
    "vulkan-1"
    }

   targetdir ("../Build/" .. OutputDir .. "/%{prj.name}")
   objdir ("../Build/Intermediates/" .. OutputDir .. "/%{prj.name}")

   filter "system:windows"
       systemversion "latest"
       defines { }

   filter "configurations:Debug"
       defines { "DEBUG" }
       runtime "Debug"
       symbols "On"

   filter "configurations:Release"
       defines { "RELEASE" }
       runtime "Release"
       optimize "On"
       symbols "On"

   filter "configurations:Dist"
       defines { "DIST" }
       runtime "Release"
       optimize "On"
       symbols "Off"