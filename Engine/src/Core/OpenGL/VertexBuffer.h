#pragma once

#include "OpenGLObject.h"
#include "BufferLayout.h"

class VertexBuffer : public OpenGLObject
{
public:

	VertexBuffer(uint32_t size);
	VertexBuffer(float* vertices, uint32_t size);

	~VertexBuffer();

	void Bind() override;

	void UnBind() override;

	void SetData(const void* data, uint32_t size);

	const BufferLayout& GetLayout() const { return m_Layout; }

	void SetLayout(const BufferLayout& layout) { m_Layout = layout;  }

	static Ref<VertexBuffer> Create(uint32_t size);
	static Ref<VertexBuffer> Create(float* vertices, uint32_t size);

private:

	BufferLayout m_Layout;
};
