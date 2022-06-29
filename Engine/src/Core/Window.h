#pragma once

#include <glad/glad.h>
#include "Core/Event.h"

struct GLFWWindow;

struct WindowSpecs
{
	using WindowEventCallback = std::function<void(Event&)>;

	int width = 1280;
	int height = 720;
	const char* title = "Window";
	bool m_VSync = false;
	WindowEventCallback  WindowCallback;
	std::string m_SplashScreenImageName;
};

class Window
{
public:
	Window(const WindowSpecs& specs = WindowSpecs());
	virtual ~Window();

	void Update();

	const bool IsOpen() const;

	void SetEventCallback(const WindowSpecs::WindowEventCallback& callback);

	void SetVSync(bool enabled);
	bool VSyncEnabled() const { return m_WindowSpecs.m_VSync; }

	struct GLFWwindow* GetNativeWindow() const { return m_Window; }
	const WindowSpecs& GetSpecs() const { return m_WindowSpecs; }

	static void glfwErrorCallback(int error, const char* description);

	class SplashScreen* GetSplashScreen() { return m_SplashScreen;  }

private:

	
	class OpenGlContext* m_Context;

	struct GLFWwindow* m_Window;

	WindowSpecs m_WindowSpecs;

	class SplashScreen* m_SplashScreen;
};