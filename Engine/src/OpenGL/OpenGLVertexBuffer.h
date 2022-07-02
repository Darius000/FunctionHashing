#pragma once

#include "Renderer/VertexBuffer.h"
#include "Renderer/BufferLayout.h"

class OpenGLVertexBuffer : public VertexBuffer
{
public:

	OpenGLVertexBuffer(uint32_t size);
	OpenGLVertexBuffer(float* vertices, uint32_t size);

	~OpenGLVertexBuffer();

	void Bind() override;

	void UnBind() override;

	void SetData(const void* data, uint32_t size);

	const BufferLayout& GetLayout() const { return m_Layout; }

	void SetLayout(const BufferLayout& layout) { m_Layout = layout;  }

private:

	BufferLayout m_Layout;
};
