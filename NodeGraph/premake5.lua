project "NodeGraph"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
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
		"NodeEditor",
		"Engine"
	}
	
	defines
    {
        "_CRT_SECURE_NO_WARNINGS",
		"NOMINMAX"
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
	  