#include "PCH.h"
#include "OpenGlContext.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Core/Log.h"


OpenGlContext::OpenGlContext(GLFWwindow* windowHandle)
	:m_WindowHandle(windowHandle)
{

}

void OpenGlContext::Init()
{
	glfwMakeContextCurrent(m_WindowHandle);

	int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	LOG_INFO("GL status = {0}", status);

	glLineWidth(1.0f);
	glEnable(GL_LINE_SMOOTH);
}

void OpenGlContext::SwapBuffers()
{
	glfwSwapBuffers(m_WindowHandle);
}