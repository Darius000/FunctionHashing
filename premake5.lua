include "Dependencies.lua"

workspace "NodeEngine"
	architecture "x64"
	configurations { "Debug", "Release", "Dist"}
	startproject "NodeGraph"

	flags
	{
		"MultiProcessorCompile"
	}
	
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"


group "Dependencies"
	include "BHive/vendor/glfw"
	include "BHive/vendor/Glad"
	include "BHive/vendor/imgui"
	include "Engine/vendor/yaml-cpp"
	include "Engine/vendor/rttr"
	include "Engine/vendor/imgui-node-editor"
group ""

group "Core"
	include "BHive"
group ""

include "Engine"
include "NodeGraph"





