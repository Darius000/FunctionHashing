#pragma once

#include "Core/Core.h"
#include "Timer.h"

struct GLFWwindow;

class SplashScreen
{
public:
	SplashScreen( const std::string& filename);
	~SplashScreen();

	void Begin(float minimumDuration = 3.0f);
	void End();

protected:

	float m_EndTime;

	BHive::Timer m_Timer;

	class Texture* m_Image;

	struct GLFWwindow* m_SplashScreenWindow;

	struct GLFWwindow* m_ApplicationWindow;

	class Mesh* m_Quad;

};

