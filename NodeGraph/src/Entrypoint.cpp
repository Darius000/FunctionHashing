// FunctionHashing.cpp : Defines the entry point for the application.
//
#include "PCH.h"


#include <imgui.h>
#include <imgui_internal.h>

#include <examples/imgui_impl_glfw.h>
#include <examples/imgui_impl_opengl3.h>


#include "Core/Application.h"
#include "Functions/Functions.h"
#include <any>

float multiply(float a, float b)
{
	return a * b;
}

void PrintMe(const std::string& str)
{
	std::cout << str << "\n";
}

struct Class
{
	static void staticrun(){ std::cout << "staticrun" << "\n"; };
	void run() const {std::cout<< "const run" << "\n"; };
	void runnonconst() { std::cout << " run" << "\n"; }

};

DEFINE_FUNCTION_WRAPPER(multi, multiply);
DEFINE_FUNCTION_WRAPPER(Prin, PrintMe);
DEFINE_FUNCTION_WRAPPER(SRun, Class::staticrun);
DEFINE_FUNCTION_WRAPPER(Run, Class::run);
DEFINE_FUNCTION_WRAPPER(RunN, Class::runnonconst);


int main(int argc, char* argv[])
{
	std::vector<Function*> functions;


	functions.push_back(&multi::ptr);
	auto z = functions[0];
	auto fz = Cast<FunctionWrapper<multi::Type>>(z);
	float w = (*fz)(10.0f, 20.0f);
	std::cout << w << "\n";
	
	float b = multi::ptr(30.0f, 30.0f);
	Prin::ptr("name");
	SRun::ptr();

	Class* c = new Class();
	const Class* f = new Class();
	Class d;
	const Class e = d;
	Run::ptr(e);
	Run::ptr(d);
	Run::ptr(c);
	Run::ptr(f);
	RunN::ptr(d);
	RunN::ptr(c);

	delete c;

   Application* app = new Application();

   app->Run();
   delete app;

   return 0;
}
