#include "PCH.h"
#include "OpenGLIndexBuffer.h"
#include <glad/glad.h>

OpenGlIndexBuffer::OpenGlIndexBuffer(uint32_t* indices, uint32_t count)
	:m_Count(count)
{
	glCreateBuffers(1, &m_RendererID);

	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	glBufferData(GL_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
}

OpenGlIndexBuffer::~OpenGlIndexBuffer()
{
	glDeleteBuffers(1, &m_RendererID);
}

void OpenGlIndexBuffer::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
}

void OpenGlIndexBuffer::UnBind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
