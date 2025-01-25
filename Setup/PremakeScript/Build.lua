-- premake5.lua
workspace "GemEngine"
   location ("../../")
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }
   startproject "GemProject"

   -- Workspace-wide build options for MSVC
   filter "system:windows"
      buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus" }

OutputDir = "%{cfg.system}-%{cfg.architecture}/%{cfg.buildcfg}"

group "Engine"
	include "../../GemEngine/Build-Engine.lua"
group ""

include "../../GemProject/Build-Project.lua"