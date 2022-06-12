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
	include "Engine/vendor/glfw"
	include "Engine/vendor/Glad"
	include "Engine/vendor/imgui"
	include "Engine/vendor/yaml-cpp"
	include "Engine/vendor/rttr"
	include "Engine/vendor/header-parser"
	include "Engine/vendor/imgui-node-editor"
group ""

include "Engine"
include "NodeGraph"





