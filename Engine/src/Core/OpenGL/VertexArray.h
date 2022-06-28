#pragma once

#include "Core/Core.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

class VertexArray : public OpenGLObject
{
public:

	VertexArray();

	~VertexArray();

	void Bind() override;

	void UnBind() override;

	void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer);
	void SetIndexBuffer(const Ref<IndexBuffer> &indexBuffer);

	const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const { return m_VertexBuffers; }
	const Ref<IndexBuffer>& GetIndexBuffer() const { return m_IndexBuffer; }


	static Ref<VertexArray> Create();

private:

	uint32_t m_VertexBufferIndex = 0;
	std::vector<Ref<VertexBuffer>> m_VertexBuffers;
	Ref<IndexBuffer> m_IndexBuffer;
};

