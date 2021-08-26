project "yaml-cpp"
    kind "StaticLib"
    language "C++"
    
    targetdir ("lib/%{prj.name}")
    objdir ("bin-int/" ..outputdir.. "/%{prj.name}")
    
    files
    {
        "**.cpp",
		"**.h"
    }
	
	includedirs
	{
		""
	}
    
    
    --configuration "windows"
   -- postbuildcommands{"{COPY} $(TargetPath) $(SolutionDir)\\scripts"}
	filter "system:windows"
		systemversion "latest"
		cppdialect "C++17"
		staticruntime "On"
		
	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"
		