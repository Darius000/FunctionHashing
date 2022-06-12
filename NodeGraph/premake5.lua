project "NodeGraph"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"
	
	targetdir ("%{wks.location}/bin/" ..outputdir.. "/%{prj.name}")
    objdir ("%{wks.location}/bin-int/" ..outputdir.. "/%{prj.name}")
	

	files 
	{
		"src/**.h", 
		"src/**.cpp", 
		"src/**.hpp",
		"src/**.inl"
	}


	includedirs
	{
		"Generated",
		"src",
		"%{IncludeDirs.GLM}",
		"%{IncludeDirs.YAML}",
		"%{IncludeDirs.Reflection}",
		"%{wks.location}/Engine/vendor",
		"%{IncludeDirs.IMGUI}",
		"%{IncludeDirs.GLAD}",
		"%{wks.location}/Engine/src",
		"%{wks.location}/Engine/src/Core"
	}
	
	links
	{	
		"Engine"
	}
	
	defines
    {
        "_CRT_SECURE_NO_WARNINGS",
		"NOMINMAX",
		"YAML_CPP_STATIC_DEFINE",
		"YAML_CPP_DEPRECATED_NO_EXPORT"
    }

	filter "system:windows"
		systemversion "latest"

		
		defines
		{
			"_CRT_SECURE_NO_WARNINGS",
			"NOMINMAX"
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
	  