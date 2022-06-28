#include "PCH.h"
#include "Application.h"
#include "ImGui/ImGuiLayer.h"
#include "Debug/Instrumentor.h"
#include <GLFW/glfw3.h>

Application::Application(const std::string& name , ApplicationCommandLineArgs args)
{
	PROFILE_FUNCTION();

	m_CommandLineArgs = args;

	s_Instance = this;

	WindowSpecs specs;
	specs.m_SplashScreenImageName = "resources/splash_test.png";

	m_Window = MakeScope<Window>(specs);

	m_Window->SetEventCallback(BIND_EVENT(this, OnEvent));

	m_ImGuiLayer = new ImGuiLayer();

	PushLayer(m_ImGuiLayer);

	m_Window->GetSplashScreen()->End();
}

Application::~Application()
{
	PROFILE_FUNCTION();

	Shutdown();
}

void Application::PushLayer(class Layer* layer)
{
	m_LayerStack.PushLayer(layer);
	layer->OnAttach();
}

void Application::PopLayer(class Layer* layer)
{
	m_LayerStack.PopLayer(layer);
	layer->OnDetach();
}


void Application::Run()
{
	PROFILE_FUNCTION();

	while (m_Running)
	{
		m_Time = (float)glfwGetTime();
		m_DeltaTime = m_Time > 0.0f ? m_Time - m_LastTime : (1.0f / 60.0f);
		m_LastTime = m_Time;
		
		if (!m_Minimized)
		{
			glClearColor(1.0f, .5f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			{
				for (Layer* layer : m_LayerStack)
				{
					layer->OnUpdate(m_DeltaTime);
				}
			}

			m_ImGuiLayer->OnBegin();

			for (Layer* layer : m_LayerStack)
			{
				layer->OnImGuiRender();
			}

			m_ImGuiLayer->OnEnd();

		}
		
		m_Window->Update();

	}

}

void Application::Shutdown()
{

}

void Application::OnEvent(Event& e)
{
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<WindowCloseEvent>(this, &Application::OnWindowClosed);
	dispatcher.Dispatch<WindowResizeEvent>(this, &Application::OnWindowResized);

	//Handle layer events

	for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
	{
		(*--it)->ProcessEvents(e);
		if (e.m_Handled)
		{
			break;
		}
	}
}

bool Application::OnWindowClosed(WindowCloseEvent& e)
{
	m_Running = false;
	return true;
}

bool Application::OnWindowResized(WindowResizeEvent& e)
{
	if (e.GetWidth() == 0 || e.GetHeight() == 0)
	{
		m_Minimized = true;
		return false;
	}

	m_Minimized = false;

	return false;
}

Application* Application::s_Instance = nullptr;
