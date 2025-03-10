project "GemEngine"
location( _SCRIPT_DIR )
kind "StaticLib"
language "C++"
cppdialect "C++20"
targetdir "Build/%{cfg.buildcfg}"
staticruntime "off"

files { 

    "GemCore/include/Gem/Core/**.h",
    "GemCore/include-protected/**.h",
    "GemCore/src/**.cpp",

    "GemWindow/include/Gem/Window/**.h",
    "GemWindow/include-protected/**.h",
    "GemWindow/src/**.cpp",

    "GemGraphics/include/Gem/Graphics/**.h",
    "GemGraphics/include-protected/**.h",
    "GemGraphics/src/**.cpp",

    "C:/stb/stb_image.cpp",
    "C:/glad/src/glad.c"
}

includedirs
{
    "GemCore/include",
    "GemCore/include-protected",

    "GemWindow/include",
    "GemWindow/include-protected",

    "GemGraphics/include",
    "GemGraphics/include-protected",

    "C:/glfw-3.4/include",
    "C:/glad/include",
    "C:/glm-1.0.1",
    "C:/stb"
}

libdirs {

    "C:/glfw-3.4/build/src/Debug",

}

links {

    "glfw3",
    "opengl32",
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