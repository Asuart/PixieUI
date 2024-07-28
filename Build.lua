-- premake5.lua
workspace "PixieUI"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }
   startproject "PixieUI"

   -- Workspace-wide build options for MSVC
   filter "system:windows"
      buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus" }

OutputDir = "%{cfg.system}-%{cfg.architecture}/%{cfg.buildcfg}"

include "Build-PixieUI.lua"