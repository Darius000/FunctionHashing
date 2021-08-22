#include "Application.h"
#include "Debug/Instrumentor.h"

int main(int argc, char* argv[])
{
	PROFILE_BEGIN_SESSION("Start", "Startup.json");

   Application* app = new Application();

   PROFILE_END_SESSION();

   PROFILE_BEGIN_SESSION("Update", "Update.json");

   app->Run();

   PROFILE_END_SESSION();

   PROFILE_BEGIN_SESSION("End", "End.json");


   delete app;


   PROFILE_END_SESSION();

   return 0;
}
