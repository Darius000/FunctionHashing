#include "PCH.h"
#include "OpenGlContext.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>


OpenGlContext::OpenGlContext(GLFWwindow* windowHandle)
	:m_WindowHandle(windowHandle)
{

}

void OpenGlContext::Init()
{
	glfwMakeContextCurrent(m_WindowHandle);

	int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	fprintf_s(stdout, "GL status = %d \n", status);

	glLineWidth(1.0f);
	glEnable(GL_LINE_SMOOTH);
}

void OpenGlContext::SwapBuffers()
{
	glfwSwapBuffers(m_WindowHandle);
}
