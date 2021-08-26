workspace "FunctionHashing"
	architecture "x64"
	configurations { "Debug", "Release"}
	
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDirs = {}
IncludeDirs["GLFW"] = "NodeGraph/vendor/GLFW/include"
IncludeDirs["GLAD"] = "NodeGraph/vendor/GLAD/include"
IncludeDirs["IMGUI"] = "NodeGraph/vendor/IMGUI"
IncludeDirs["STB_IMAGE"] = "NodeGraph/vendor/STB_IMAGE"
IncludeDirs["YAML"] = "NodeGraph/vendor/yaml-cpp"

group "Dependencies"
	include "NodeGraph/vendor/GLFW"
	include "NodeGraph/vendor/GLAD"
	include "NodeGraph/vendor/IMGUI"
	include "NodeGraph/vendor/yaml-cpp"
group ""
	
project "NodeGraph"
	location "NodeGraph"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "On"
	
	targetdir ("bin/" ..outputdir.. "/%{prj.name}")
    objdir ("bin-int/" ..outputdir.. "/%{prj.name}")
	
	pchheader "PCH.h"
	pchsource "NodeGraph/src/PCH.cpp"
	
	
	files 
	{
	"%{prj.name}/src/**.h", 
	"%{prj.name}/src/**.cpp", 
	"%{prj.name}/src/**.hpp",
	"%{prj.name}/src/**.inl",
	}
	
	includedirs
	{
		"%{prj.name}/src",
		"%{IncludeDirs.GLFW}",
		"%{IncludeDirs.GLAD}",
		"%{IncludeDirs.IMGUI}",
		"%{IncludeDirs.STB_IMAGE}",
		"%{IncludeDirs.YAML}"
	}
	
	links
	{
		"GLFW",
		"GLAD",
		"IMGUI",
		"yaml-cpp",
		 "opengl32.lib"
	}
	
	defines
    {
        "_CRT_SECURE_NO_WARNINGS"
    }
	
	filter "system:windows"
		systemversion "latest"
		
		defines
		{
			"_CRT_SECURE_NO_WARNINGS"
		}

	filter "configurations:Debug"
		defines "DEBUG"
		runtime "Debug"
		symbols "On"
		
	filter "configurations:Release"
      defines "NDEBUG"
	  runtime "Release"
      optimize "On"
	  


