// FunctionHashing.cpp : Defines the entry point for the application.
//
#include "PCH.h"


#include <imgui.h>
#include <imgui_internal.h>

#include <examples/imgui_impl_glfw.h>
#include <examples/imgui_impl_opengl3.h>


#include "Core/Application.h"
#include "Functions/Functions.h"
#include "Nodes/CustomEvent.h"

int main(int argc, char* argv[])
{

   Application* app = new Application();

   app->Run();
   delete app;

   return 0;
}
