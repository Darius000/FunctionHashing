#include "PCH.h"
#include "OpenGL/OpenGLRendererAPI.h"
#include "RendererAPI.h"

RendererAPI::API RendererAPI::s_API = RendererAPI::API::Opengl;

Scope<RendererAPI> RendererAPI::Create()
{
	switch (s_API)
	{
	case RendererAPI::API::Opengl:
		return MakeScope<OpenGLRendererAPI>();
	}

	return nullptr;
}
