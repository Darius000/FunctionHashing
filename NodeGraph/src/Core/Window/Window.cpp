#include "PCH.h"
#include "Window.h"
#include <examples/imgui_impl_glfw.h>
#include <examples/imgui_impl_opengl3.h>
#include "Core/OpenGlContext.h"
#include "Core/Events/ApplicationEvents.h"
#include "Core/Events/KeyEvents.h"
#include "Core/Events/MouseEvent.h"

static bool s_GLFWInitialized = false;


Window::Window(const WindowSpecs& specs)
	:m_Window(nullptr)
{
	m_WindowSpecs = specs;

	if (!s_GLFWInitialized)
	{
		int status = glfwInit();
		glfwSetErrorCallback(glfwErrorCallback);
		if(status) s_GLFWInitialized = true;
	}

	m_Window = glfwCreateWindow((int)m_WindowSpecs.width, (int)m_WindowSpecs.height,
		m_WindowSpecs.title, nullptr, nullptr);

	//init opengl
	m_Context = new class OpenGlContext(m_Window);
	m_Context->Init();

	////set glfw window context to opengl version 4.6
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	SetVSync(true);

	glfwSetWindowUserPointer(m_Window, &m_WindowSpecs);
	glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
	{
		WindowSpecs& specs = *(WindowSpecs*)(glfwGetWindowUserPointer(window));
		specs.width = width;
		specs.height = height;
		glViewport(0, 0, specs.width, specs.height);
		WindowResizeEvent event(width, height);
		specs.WindowCallback(event);
	});

	glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
	{
		WindowSpecs& specs = *(WindowSpecs*)(glfwGetWindowUserPointer(window));
		WindowCloseEvent event;
		specs.WindowCallback(event);
	});

	glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		WindowSpecs& specs = *(WindowSpecs*)glfwGetWindowUserPointer(window);

		switch (action)
		{
		case GLFW_PRESS:
		{
			KeyPressedEvent event((EKeyCode)key, 0);
			specs.WindowCallback(event);
			break;
		}
		case GLFW_REPEAT:
		{
			KeyPressedEvent event((EKeyCode)key, 1);
			specs.WindowCallback(event);
			break;
		}
		case GLFW_RELEASE:
		{
			KeyReleasedEvent event((EKeyCode)key);
			specs.WindowCallback(event);
			break;
		}
		default:
			break;
		}
	});

	glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
	{
		WindowSpecs& specs = *(WindowSpecs*)glfwGetWindowUserPointer(window);

		switch (action)
		{
		case GLFW_PRESS:
		{
			MouseButtonPressedEvent event((EMouseButton)button);
			specs.WindowCallback(event);
			break;
		}
		case GLFW_RELEASE:
		{
			MouseButtonReleasedEvent event((EMouseButton)button);
			specs.WindowCallback(event);
			break;
		}
		default:
			break;
		}
	});

	glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
	{
		WindowSpecs& specs = *(WindowSpecs*)glfwGetWindowUserPointer(window);

		MouseScrolledEvent event((float)xOffset, (float)yOffset);
		specs.WindowCallback(event);
	});

	glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
	{
		WindowSpecs& specs = *(WindowSpecs*)glfwGetWindowUserPointer(window);

		MouseMovedEvent event((float)xPos, (float)yPos);
		specs.WindowCallback(event);
	});
}

Window::~Window()
{
	delete m_Context;
	glfwDestroyWindow(m_Window);

	LOG("Destroyed Window : %s", m_WindowSpecs.title);
}

void Window::Update()
{
	glfwPollEvents();

	m_Context->SwapBuffers();

}	

const bool Window::IsOpen() const
{
	return !glfwWindowShouldClose(m_Window);
}

void Window::SetEventCallback(const WindowSpecs::WindowEventCallback& callback)
{
	m_WindowSpecs.WindowCallback = callback;
}

void Window::SetVSync(bool enabled)
{
	glfwSwapInterval(enabled ? 1 : 0);

	m_WindowSpecs.m_VSync = enabled;
}

void Window::glfwErrorCallback(int error, const char* description)
{
	LOG("Error : %s", description)
}

