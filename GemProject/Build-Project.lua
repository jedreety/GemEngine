project "GemProject"
   location( _SCRIPT_DIR )
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++20"
   targetdir "Build/%{cfg.buildcfg}"
   staticruntime "off"

   files { "src/**.h", "src/**.cpp" }

   includedirs
   {

	  -- Include Core
      "../GemEngine/GemCore/include",

      -- Include Window
      "../GemEngine/GemWindow/include",

        -- Include Graphics
        "../GemEngine/GemGraphics/include",
   
        "C:/glfw-3.4/include",
        "C:/glad/include",
        "C:/glm-1.0.1",
        "C:/stb"
   }
  
   libdirs {

    "C:/glfw-3.4/build/src/Debug",
 }

   links
   {
      "GemEngine",
      "glfw3",
      "opengl32"
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