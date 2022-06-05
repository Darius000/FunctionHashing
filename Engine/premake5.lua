project "Engine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	
	targetdir ("%{wks.location}/bin/" ..outputdir.. "/%{prj.name}")
    objdir ("%{wks.location}/bin-int/" ..outputdir.. "/%{prj.name}")

	pchheader "PCH.h"
	pchsource "src/PCH.cpp"
	
	
	
	files 
	{
		"src/**.h", 
		"src/**.cpp", 
		"src/**.hpp",
		"src/**.inl"
	}


	includedirs
	{
		"src",
		"src/Core",
		"%{wks.location}/vendor",
		"%{IncludeDirs.GLFW}",
		"%{IncludeDirs.GLAD}",
		"%{IncludeDirs.IMGUI}",
		"%{IncludeDirs.STB_IMAGE}",
		"%{IncludeDirs.YAML}",
		"%{IncludeDirs.GLM}",
		"%{IncludeDirs.Reflection}"
	}
	
	defines
    {
        "_CRT_SECURE_NO_WARNINGS",
		"NOMINMAX"
    }

	links
	{
		"GLFW",
		"GLAD",
		"IMGUI",
		"yaml-cpp",
		"Reflection",
		 "opengl32.lib"
	}

	filter "files:src/Core/Entrypoint.cpp"
		flags{ "NoPCH" }

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
	
	