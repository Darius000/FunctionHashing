project "Engine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
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
		"%{wks.location}/BHive/stb_image/**.h",
		"%{wks.location}/BHive/stb_image/**.cpp",
		"%{wks.location}/BHive/glm/glm/**.inl",
		"%{wks.location}/BHive/glm/glm/**.hpp"
	}


	includedirs
	{
		"src",
		"%{wks.location}/BHive/src",
		"%{IncludeDirs.GLFW}",
		"%{IncludeDirs.GLAD}",
		"%{IncludeDirs.IMGUI}",
		"%{IncludeDirs.STB_IMAGE}",
		"%{IncludeDirs.YAML}",
		"%{IncludeDirs.GLM}",
		"%{IncludeDirs.Reflection}",
		"%{IncludeDirs.SPDLOG}"
	}
	
	defines
    {
        "_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE",
		"NOMINMAX",
		"YAML_CPP_STATIC_DEFINE",
		"YAML_CPP_DEPRECATED_NO_EXPORT"
    }

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"yaml-cpp",
		"rttr",
		"BHive",
		"imgui-node-editor",
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
	
	