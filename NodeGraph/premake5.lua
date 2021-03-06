project "NodeGraph"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "off"
	
	targetdir ("%{wks.location}/bin/" ..outputdir.. "/%{prj.name}")
    objdir ("%{wks.location}/bin-int/" ..outputdir.. "/%{prj.name}")
	

	files 
	{
		"src/**.h", 
		"src/**.cpp", 
		"src/**.hpp",
		"src/**.inl",
		"Generated/**.cpp"
	}


	includedirs
	{
		"Generated",
		"src",
		"%{wks.location}/BHive/src",
		"%{IncludeDirs.GLM}",
		"%{IncludeDirs.YAML}",
		"%{IncludeDirs.Reflection}",
		"%{wks.location}/Engine/vendor",
		"%{IncludeDirs.IMGUI}",
		"%{IncludeDirs.GLAD}",
		"%{wks.location}/Engine/src",
		"%{IncludeDirs.SPDLOG}"
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
      	defines "RELEASE"
	  	runtime "Release"
      	optimize "On"
		symbols "On"

	filter "configurations:Dist"
		kind "WindowedApp"
      	defines "DIST"
	  	runtime "Release"
      	optimize "On"
		symbols "off"
	  