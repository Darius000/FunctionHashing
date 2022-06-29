#pragma once

#include "Core/Core.h"
#include "Layer.h"
#include "Window.h"
#include "SplashScreen.h"
#include "Events/ApplicationEvents.h"
#include "Event.h"

struct ApplicationCommandLineArgs
{
	int m_Count = 0;
	char** m_Args = nullptr;

	const char* operator[](int index) const
	{
		if (index > m_Count) return nullptr;

		return m_Args[index];
	}
};

class Application
{
public:
	Application(const std::string& name = "Engine App", ApplicationCommandLineArgs args = ApplicationCommandLineArgs() );
	~Application();

	void PushLayer(class Layer* layer);
	void PopLayer(class Layer* layer);

	void Run();
	void Shutdown();

	static inline Application& Get() { return *s_Instance;}

	inline class Window& GetWindow() { return *m_Window.get(); }

	void OnEvent(Event& e);

	bool OnWindowClosed(WindowCloseEvent& e);
	bool OnWindowResized(WindowResizeEvent& e);

	ApplicationCommandLineArgs GetCommandArgs() const { return m_CommandLineArgs; }

private:
	static Application* s_Instance;

	Scope<class Window> m_Window;

	class LayerStack m_LayerStack;

	class ImGuiLayer* m_ImGuiLayer;

	float m_Time;
	float m_DeltaTime;
	float m_LastTime;

	bool m_Running = true;
	bool m_Minimized = false;

	ApplicationCommandLineArgs m_CommandLineArgs;
};

Application* CreateApplication(ApplicationCommandLineArgs args);