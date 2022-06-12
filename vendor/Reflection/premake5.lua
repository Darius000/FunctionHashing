project "Reflection"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("%{wks.location}/bin/" ..outputdir.. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" ..outputdir.. "/%{prj.name}")

	files
	{
		"src/rttr/**.cpp",
		"src/rttr/**.h",
		"src/rttr/**.inl",
		"src/rttr/**.hpp",
	}

	includedirs
	{
		"src/rttr"
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

	filter "configurations:Dist"
      defines "DIST"
	  runtime "Release"
      optimize "On"