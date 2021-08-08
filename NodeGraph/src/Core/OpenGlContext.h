#pragma once

struct GLFWwindow;

class OpenGlContext
{
public:
	OpenGlContext(GLFWwindow* windowHandle);

	void Init();

	void SwapBuffers();


private:
	GLFWwindow* m_WindowHandle;
};