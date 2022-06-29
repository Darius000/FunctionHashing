#pragma once

#include "Core/Core.h"

class Shader;

class VertexArray;

struct Vertex
{
	glm::vec3 m_Position;
	glm::vec2 m_TexCoord;
};

class Mesh
{
public:
	Mesh();

	void Draw();

private:

	Ref<VertexArray> m_VertexArray;

	Ref<Shader> m_Shader;
};