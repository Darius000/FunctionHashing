project "NodeGraph"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "On"
	
	targetdir ("%{wks.location}/bin/" ..outputdir.. "/%{prj.name}")
    objdir ("%{wks.location}/bin-int/" ..outputdir.. "/%{prj.name}")
	

	files 
	{
		"src/**.h", 
		"src/**.cpp", 
		"src/**.hpp",
		"src/**.inl",	
	}


	includedirs
	{
		"Generated",
		"src",
		"%{IncludeDirs.GLFW}",
		"%{IncludeDirs.GLAD}",
		"%{IncludeDirs.IMGUI}",
		"%{IncludeDirs.YAML}",
		"%{IncludeDirs.GLM}",
		"%{IncludeDirs.Reflection}",
		"%{wks.location}/Engine/src",
		"%{wks.location}/Engine/src/Core",
		"%{wks.location}/NodeEditor/src"
	}
	
	links
	{	
		"HeaderParser",
		"NodeEditor",
		"Engine"
	}
	
	defines
    {
        "_CRT_SECURE_NO_WARNINGS",
		"NOMINMAX"
    }

	prebuildcommands
	{
		"%{wks.location}scripts/HeaderParser.exe"
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

	filter "configurations:Dist"
      defines "DIST"
	  runtime "Release"
      optimize "On"
	  