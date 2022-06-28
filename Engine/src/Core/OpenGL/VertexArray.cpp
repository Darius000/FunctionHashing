#include "PCH.h"
#include "VertexArray.h"
#include <glad/glad.h>

static GLenum ShaderDataTypeToGLenum(ShaderDataType type)
{
	switch (type)
	{
	case ShaderDataType::Float:		
	case ShaderDataType::Float2:
	case ShaderDataType::Float3:
	case ShaderDataType::Float4:		
	case ShaderDataType::Mat3:
	case ShaderDataType::Mat4:
		return GL_FLOAT;
	case ShaderDataType::Int:
	case ShaderDataType::Int2:
	case ShaderDataType::Int3:
	case ShaderDataType::Int4:
		return GL_INT;
	case ShaderDataType::Bool:
		return GL_BOOL;
	default:
		break;
	}

	return 0;
}

VertexArray::VertexArray()
{
	glCreateVertexArrays(1, &m_RenderID);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_RenderID);
}

void VertexArray::Bind()
{
	glBindVertexArray(m_RenderID);
}

void VertexArray::UnBind()
{
	glBindVertexArray(0);
}

void VertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
{
	glBindVertexArray(m_RenderID);
	vertexBuffer->Bind();

	const auto& layout = vertexBuffer->GetLayout();
	for (const auto& element : layout)
	{
		switch (element.m_Type)
		{
		case ShaderDataType::Float:
		case ShaderDataType::Float2:
		case ShaderDataType::Float3:
		case ShaderDataType::Float4:
		{
			glEnableVertexAttribArray(m_VertexBufferIndex);
			glVertexAttribPointer(m_VertexBufferIndex,
				element.GetComponentCount(),
				ShaderDataTypeToGLenum(element.m_Type),
				element.m_Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)element.m_Offset);

			m_VertexBufferIndex++;
			break;
		}

		case ShaderDataType::Int:
		case ShaderDataType::Int2:
		case ShaderDataType::Int3:
		case ShaderDataType::Int4:
		case ShaderDataType::Bool:
		{
			glEnableVertexAttribArray(m_VertexBufferIndex);
			glVertexAttribIPointer(m_VertexBufferIndex,
				element.GetComponentCount(),
				ShaderDataTypeToGLenum(element.m_Type),
				layout.GetStride(),
				(const void*)element.m_Offset);

			m_VertexBufferIndex++;
			break;
		}

		case ShaderDataType::Mat3:
		case ShaderDataType::Mat4:
		{
			uint8_t count = element.GetComponentCount();
			for (uint8_t i = 0; i < count; i++)
			{
				glEnableVertexAttribArray(m_VertexBufferIndex);
				glVertexAttribPointer(m_VertexBufferIndex,
					count,
					ShaderDataTypeToGLenum(element.m_Type),
					element.m_Normalized ? GL_TRUE : GL_FALSE,
					layout.GetStride(),
					(const void*)(element.m_Offset + sizeof(float) * count * i));
				glVertexAttribDivisor(m_VertexBufferIndex, 1);

				m_VertexBufferIndex++;
				
			}
			break;
		}
		}
	}

	m_VertexBuffers.push_back(vertexBuffer);
}

void VertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
{
	glBindVertexArray(m_RenderID);
	indexBuffer->Bind();

	m_IndexBuffer = indexBuffer;
}

Ref<VertexArray> VertexArray::Create()
{
	return MakeRef<VertexArray>();
}
