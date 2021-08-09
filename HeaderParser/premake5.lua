project "HeaderTool"
    kind "ConsoleApp"
    language "C#"
    
    targetdir ("bin/" ..outputdir.. "/%{prj.name}")
    objdir ("bin-int/" ..outputdir.. "/%{prj.name}")
    
    files
    {
        "**.cs"
    }
    
    includedirs
    {
        "%{prj.name}/src"
    }
    
    --configuration "windows"
   -- postbuildcommands{"{COPY} $(TargetPath) $(SolutionDir)\\scripts"}
    
    filter"system:windows"
        systemversion "latest"

        filter "configurations:Debug"
            defines "HEADER_TOOL_DEBUG"
            runtime "Debug"
            symbols "on"

        filter "configurations:Release"
            defines "HEADER_TOOL_RELEASE"
            runtime "Release"
            optimize "on"

        filter "configurations:Dist"
            defines "HEADER_TOOL_DIST"
            runtime "Release"
            optimize "on"
