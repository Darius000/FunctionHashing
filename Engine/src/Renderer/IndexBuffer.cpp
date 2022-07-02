#include "PCH.h"
#include "IndexBuffer.h"
#include "OpenGL/OpenGLIndexBuffer.h"
#include "Renderer/RendererAPI.h"

Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count)
{
	switch (RendererAPI::GetAPI())
	{
	case RendererAPI::API::Opengl :
		return MakeRef<OpenGlIndexBuffer>(indices, count);
	default:
		break;

	}

	return nullptr;
}
