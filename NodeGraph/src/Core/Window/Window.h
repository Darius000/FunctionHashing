#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Core/Event.h"


struct WindowSpecs
{
	using WindowEventCallback = std::function<void(Event&)>;

	int width = 1280;
	int height = 720;
	const char* title = "Window";
	bool m_VSync = false;
	WindowEventCallback  WindowCallback;
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

	GLFWwindow* GetNativeWindow() const { return m_Window; }
	const WindowSpecs& GetSpecs() const { return m_WindowSpecs; }

	static void glfwErrorCallback(int error, const char* description);


private:

	
	class OpenGlContext* m_Context;

	GLFWwindow* m_Window;

	WindowSpecs m_WindowSpecs;

};