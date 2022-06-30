#pragma once

#include "Layer.h"
#include <memory>
#include <vector>
#include <string>
#include <stdint.h>
#include <functional>

struct GLFWwindow;

namespace BHive
{
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

	struct ApplicationSpecification
	{
		std::string m_Name;
		uint32_t m_Width = 1600;
		uint32_t m_Height = 900;
	};

	class Application
	{
	public:
		Application(const ApplicationSpecification& applicationspecification = ApplicationSpecification(), ApplicationCommandLineArgs args = ApplicationCommandLineArgs());
		~Application();

		template<typename T>
		void PushLayer()
		{
			static_assert(std::is_base_of<Layer, T>::value, "Type is not subclass of Layer");
			m_LayerStack.emplace_back(std::make_shared<T>())->OnAttach();
		}

		void PushLayer(const std::shared_ptr<Layer>& layer)
		{
			m_LayerStack.emplace_back(layer); layer->OnAttach();
		}

		void Run();
		void SetMenuBarCallback(const std::function<void()>& menubarCallback) { m_MenuBarCallback = menubarCallback; }

		void Close();

		void SetDefaultTheme();

	private:
		void Init();
		void Shutdown();

	public:
		static inline Application& Get() { return *s_Instance; }

		GLFWwindow* GetNativeWindow() { return m_Window; }

		ApplicationCommandLineArgs GetCommandArgs() const { return m_CommandLineArgs; }

	private:
		static Application* s_Instance;

		GLFWwindow* m_Window;

		std::vector<std::shared_ptr<Layer>> m_LayerStack;
		std::function<void()> m_MenuBarCallback;

		float m_Time;
		float m_DeltaTime;
		float m_LastTime;

		bool m_Running = true;
		bool m_Minimized = false;

		ApplicationCommandLineArgs m_CommandLineArgs;
		ApplicationSpecification m_Specification;
	};

	Application* CreateApplication(int argc, char** argv);
}