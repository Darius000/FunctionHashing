#pragma once


#include "Renderer/VertexArray.h"

class OpenGLVertexArray : public VertexArray
{
public:

	OpenGLVertexArray();

	~OpenGLVertexArray();

	void Bind() override;

	void UnBind() override;

	void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) override;
	void SetIndexBuffer(const  Ref<IndexBuffer> &indexBuffer) override;

	const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const override { return m_VertexBuffers; }
	const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const override { return m_IndexBuffer; }

private:

	uint32_t m_VertexBufferIndex = 0;
	std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
	std::shared_ptr<IndexBuffer> m_IndexBuffer;
};

