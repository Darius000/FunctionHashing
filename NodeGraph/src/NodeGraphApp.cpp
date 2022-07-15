#include <Engine.h>
#include <Entrypoint.h>

#include "GraphLayer.h"
#include "Core/SplashScreen.h"

BHive::Application* BHive::CreateApplication(int argc, char** argv)
{
	Log::Init();

	BHive::ApplicationSpecification spec;
	spec.m_Name = "Node Editor";

	BHive::Application* app = new BHive::Application(spec, { argc, argv });

	SplashScreen m_SplashScreen = SplashScreen("resources/splash_test.png");
	m_SplashScreen.Begin();

	app->PushLayer<GraphLayer>();
	app->SetMenuBarCallback([app]() 
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Exit"))
				{
					app->Close();
				}



				ImGui::EndMenu();
			}
			
		});

	m_SplashScreen.End();

	return app;
}