#include "PCH.h"
#include "SplashScreen.h"
#include "Renderer/Texture.h"
#include <GLFW/glfw3.h>
#include "Renderer/Mesh.h"
#include "Renderer/RenderCommand.h"
#include "imgui.h"
#include "examples/imgui_impl_glfw.h"
#include "examples/imgui_impl_opengl3.h"
#include "glad/glad.h"


SplashScreen::SplashScreen(const std::string& filename)
	:m_EndTime(), m_ApplicationWindow(nullptr), m_SplashScreenWindow(nullptr), m_Quad(nullptr)
{
	m_Image = Texture::Create(filename);
}

SplashScreen::~SplashScreen()
{
	
}

void SplashScreen::Begin(float minimumDuration)
{

	m_EndTime = m_Timer.GetElapsedTime() + minimumDuration;
	m_ApplicationWindow = glfwGetCurrentContext();

	glfwHideWindow(m_ApplicationWindow);
	glfwWindowHint(GLFW_DECORATED, 0);
	m_SplashScreenWindow = glfwCreateWindow(m_Image->GetWidth(), m_Image->GetHeight(), "SplashScreen", nullptr, m_ApplicationWindow);

	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);

	glfwSetWindowPos(m_SplashScreenWindow, (mode->width - m_Image->GetWidth()) / 2, (mode->height - m_Image->GetHeight()) / 2);

	glfwWindowHint(GLFW_DECORATED, true);
	
	glfwMakeContextCurrent(m_SplashScreenWindow);

	RenderCommand::Init();
	RenderCommand::SetClearColor({ 1.0f, .5f, 0.0f, 1.0f });
	RenderCommand::Clear();

	m_Quad = MakeRef<Mesh>();
	m_Image->Bind(0);
	m_Quad->Draw();


	glfwSwapBuffers(m_SplashScreenWindow);

	RenderCommand::Flush();

	glfwMakeContextCurrent(m_ApplicationWindow);

}

void SplashScreen::End()
{
	if (!m_ApplicationWindow || !m_SplashScreenWindow)
	{
		return;
	}

	while (m_EndTime > m_Timer.GetElapsedTime())
	{
		Sleep(1);
	}

	glfwDestroyWindow(this->m_SplashScreenWindow);
	m_SplashScreenWindow = nullptr;

	glfwShowWindow(m_ApplicationWindow);
}
