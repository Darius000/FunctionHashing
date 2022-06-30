#pragma once
#include "Application.h"

extern BHive::Application* BHive::CreateApplication(int argc, char** argv);

bool g_ApplicationRunning = true;


namespace BHive
{
	int Main(int argc, char** argv)
	{
		while (g_ApplicationRunning)
		{
			Application* app = CreateApplication(argc, argv );

			app->Run();

			delete app;
		}

		return 0;
	}
}

#ifdef DIST

#include <Windows.h>

int WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
{
	return BHive::Main(__argc, __argv);
}

#else

int main(int argc, char** argv)
{
	return BHive::Main(argc, argv);
}

#endif