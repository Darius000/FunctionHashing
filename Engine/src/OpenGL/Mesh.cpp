#include "PCH.h"
#include "Mesh.h"
#include <glad/glad.h>
#include "Shader.h"
#include "VertexArray.h"

Mesh::Mesh()
{
	m_Shader = MakeRef<Shader>("resources/Texture.glsl");

	Vertex vertices[] =
	{
		{{-1.0f, -1.0f, 0.0f},	{0.0f,0.0f}},	//Bottom left
		{{-1.0f, 1.0f, 0.0f},	{0.0f,1.0f}},	//Top Left
		{{1.0f, 1.0f, 0.0f},	{1.0f,1.0f}},	//Top Right
		{{1.0f,-1.0f, 0.0f},	{1.0f,0.0f}}	//Bottom Right
	};

	uint32_t indices[] =
	{
		0 , 1, 2, 2, 3, 0
	};

	auto vertexBuffer = VertexBuffer::Create(4 * sizeof(Vertex));
	vertexBuffer->SetLayout({
		{ShaderDataType::Float3, "a_Position"},
		{ShaderDataType::Float2, "a_TexCoord"}
		});
	vertexBuffer->SetData(vertices, sizeof(vertices));

	auto indexBuffer = IndexBuffer::Create(indices , 6);

	m_VertexArray = VertexArray::Create();
	m_VertexArray->SetIndexBuffer(indexBuffer);
	m_VertexArray->AddVertexBuffer(vertexBuffer);
}

void Mesh::Draw()
{
	m_Shader->Bind();

	m_VertexArray->Bind();
	auto count = m_VertexArray->GetIndexBuffer()->GetCount();
	glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);

	m_VertexArray->UnBind();

	m_Shader->UnBind();
}
