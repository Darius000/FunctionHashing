project "Engine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"
	
	targetdir ("%{wks.location}/bin/" ..outputdir.. "/%{prj.name}")
    objdir ("%{wks.location}/bin-int/" ..outputdir.. "/%{prj.name}")

	pchheader "PCH.h"
	pchsource "src/PCH.cpp"
	
	
	
	files 
	{
		"src/**.h", 
		"src/**.cpp", 
		"src/**.hpp",
		"src/**.inl",
		"vendor/stb_image/**.h",
		"vendor/stb_image/**.cpp",
		"vendor/glm/glm/**.inl",
		"vendor/glm/glm/**.hpp"
	}


	includedirs
	{
		"src",
		"src/Core",
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
		"GLFW_INCLUDE_NONE",
		"NOMINMAX"
    }

	links
	{
		"GLFW",
		"GLAD",
		"IMGUI",
		"yaml-cpp",
		"rttr",
		"imgui-node-editor",
		 "opengl32.lib"
	}

	filter "files:src/Core/Entrypoint.cpp"
		flags{ "NoPCH" }

	filter "system:windows"
		systemversion "latest"
		staticruntime "On"
		
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
	
	