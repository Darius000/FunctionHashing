#include "PCH.h"
#include "IndexBuffer.h"
#include <glad/glad.h>

IndexBuffer::IndexBuffer(uint32_t* indices, uint32_t count)
	:m_Count(count)
{
	glCreateBuffers(1, &m_RenderID);

	glBindBuffer(GL_ARRAY_BUFFER, m_RenderID);
	glBufferData(GL_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &m_RenderID);
}

void IndexBuffer::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RenderID);
}

void IndexBuffer::UnBind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count)
{
	return MakeRef<IndexBuffer>(indices, count);
}
