project "GemProject"
   location( _SCRIPT_DIR )
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++20"
   targetdir "Build/%{cfg.buildcfg}"
   staticruntime "off"

   files { "Source/**.h", "Source/**.cpp" }

   includedirs
   {
      "Source",

	  -- Include Core
      "../GemEngine/GemCore/include",
      "../GemEngine/GemInput/include",
      "../GemEngine/GemWindow/include",
      "C:/glfw-3.4/include",
      "C:/VulkanSDK/1.3.296.0/Include",
      "C:/glm-1.0.1/glm"
   }
  
   libdirs {
    "C:/glfw-3.4/build/src/Debug",
    "C:/VulkanSDK/1.3.296.0/Lib"
 }

   links
   {
      "GemEngine",
      "glfw3",
      "vulkan-1"
   }

   targetdir ("../Build/" .. OutputDir .. "/%{prj.name}")
   objdir ("../Build/Intermediates/" .. OutputDir .. "/%{prj.name}")

   filter "system:windows"
       systemversion "latest"
       defines { "WINDOWS" }

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