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
	include "vendor/GLFW"
	include "vendor/GLAD"
	include "vendor/IMGUI"
	include "vendor/yaml-cpp"
	include "vendor/Reflection"
	include "HeaderParser"
group ""

include "Engine"
include "NodeEditor"
include "NodeGraph"





