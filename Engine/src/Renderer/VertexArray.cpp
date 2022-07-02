#include "PCH.h"
#include "OpenGL/OpenGLVertexArray.h"
#include "Renderer/RendererAPI.h"

Ref<VertexArray> VertexArray::Create()
{
	switch (RendererAPI::GetAPI())
	{
	case RendererAPI::API::Opengl:
		return MakeRef<OpenGLVertexArray>();
	default:
		break;

	}

	return nullptr;
}
