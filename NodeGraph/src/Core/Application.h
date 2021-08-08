#pragma once

#include "Core/Core.h"
#include "Layer.h"
#include "Window/Window.h"
#include "Events/ApplicationEvents.h"
#include "Event.h"

class Application
{
public:
	Application();
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
};

