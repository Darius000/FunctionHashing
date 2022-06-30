project "BHive"
	kind "StaticLib"
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
		"vendor/stb_image/**.h",
		"vendor/stb_image/**.cpp",
		"vendor/glm/glm/**.inl",
		"vendor/glm/glm/**.hpp"
	}


	includedirs
	{
		"src",
		"%{IncludeDirs.GLFW}",
		"%{IncludeDirs.GLAD}",
		"%{IncludeDirs.IMGUI}",
		"%{IncludeDirs.STB_IMAGE}",
		"%{IncludeDirs.GLM}"
	}
	
	defines
    {
        	"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE",
		"NOMINMAX",
    }

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		 "opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"
	

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
      	defines "DIST"
	  	runtime "Release"
      	optimize "On"
		symbols "off"
	
	