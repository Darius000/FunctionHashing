project "yaml-cpp"
    kind "StaticLib"
    language "C++"

	targetdir ("%{wks.location}/bin/" ..outputdir.. "/%{prj.name}")
    objdir ("%{wks.location}/bin-int/" ..outputdir.. "/%{prj.name}")
	
    files
    {
        "src/**.cpp",
		"src/**.h",
		"include/**.h"
    }
	
	includedirs
	{
		"include"
	}

	defines
	{
		"YAML_CPP_STATIC_DEFINE",
		"YAML_CPP_DEPRECATED_NO_EXPORT"
	}
    
    
    --configuration "windows"
   -- postbuildcommands{"{COPY} $(TargetPath) $(SolutionDir)\\scripts"}
	filter "system:windows"
		systemversion "latest"
		cppdialect "C++17"
		staticruntime "on"
		
	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"
		