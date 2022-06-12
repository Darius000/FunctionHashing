project "HeaderParser"
	kind "WindowedApp"
	language "C#"
	dotnetframework "4.8"
	csversion "10.0"

	targetdir ("%{wks.location}/bin/" ..outputdir.. "/%{prj.name}")
    objdir ("%{wks.location}/bin-int/" ..outputdir.. "/%{prj.name}")

	files
	{
		"%{wks.location}/**Build.cs",
		"src/**.cs"
	}

	includedirs
	{
		"src"
	}

	links
	{
		"System",
		"System.Windows.Forms",
		"System.Drawing"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	postbuildcommands
	{
		"copy \"HeaderParser.exe\" \"%{wks.location}scripts\""
	}

	postbuildmessage "Copying exe..."

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
