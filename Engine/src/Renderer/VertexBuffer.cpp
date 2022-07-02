#include "PCH.h"
#include "VertexBuffer.h"
#include "RendererAPI.h"
#include "OpenGL/OpenGLVertexBuffer.h"

Ref<VertexBuffer> VertexBuffer::Create(uint32_t size)
{
	switch (RendererAPI::GetAPI())
	{
	case RendererAPI::API::Opengl:
		return MakeRef<OpenGLVertexBuffer>(size);
	default:
		break;
	}

	return nullptr;
}

Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
{
	switch (RendererAPI::GetAPI())
	{
	case RendererAPI::API::Opengl:
		return MakeRef<OpenGLVertexBuffer>(vertices, size);
	default:
		break;
	}

	return nullptr;
}
