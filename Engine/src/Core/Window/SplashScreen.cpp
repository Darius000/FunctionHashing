#include "PCH.h"
#include "SplashScreen.h"
#include "Texture/Texture.h"
#include <GLFW/glfw3.h>
#include "OpenGlContext.h"
#include "OpenGL/Mesh.h"

SplashScreen::SplashScreen(const std::string& filename)
	:m_EndTime(), m_ApplicationWindow(nullptr), m_SplashScreenWindow(nullptr), m_Quad(nullptr)
{
	m_Image = new Texture(filename);
}

SplashScreen::~SplashScreen()
{
	delete m_Image;
	delete m_Quad;
}

void SplashScreen::Begin(float minimumDuration)
{

	m_EndTime = (float)glfwGetTime() + minimumDuration;
	m_ApplicationWindow = glfwGetCurrentContext();

	glfwHideWindow(m_ApplicationWindow);
	glfwWindowHint(GLFW_DECORATED, GL_FALSE);
	m_SplashScreenWindow = glfwCreateWindow(m_Image->GetWidth(), m_Image->GetHeight(), "SplashScreen", nullptr, m_ApplicationWindow);

	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);

	glfwSetWindowPos(m_SplashScreenWindow, (mode->width - m_Image->GetWidth()) / 2, (mode->height - m_Image->GetHeight()) / 2);

	glfwWindowHint(GLFW_DECORATED, true);
	
	glfwMakeContextCurrent(m_SplashScreenWindow);

	glClearColor(0, 0, 1 , 1);
	glClear(GL_COLOR_BUFFER_BIT);

	m_Quad = new Mesh();

	glfwSwapBuffers(m_SplashScreenWindow);

	glFlush();

	glfwMakeContextCurrent(m_ApplicationWindow);

}

void SplashScreen::End()
{
	if (!m_ApplicationWindow || !m_SplashScreenWindow)
	{
		return;
	}

	while (m_EndTime > glfwGetTime())
	{
		Sleep(1);
	}

	glfwDestroyWindow(this->m_SplashScreenWindow);
	m_SplashScreenWindow = nullptr;

	glfwShowWindow(m_ApplicationWindow);
}
