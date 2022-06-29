#pragma once

#include "VertexBuffer.h"
#include "Shader.h"

class Mesh
{
public:
	Mesh();

	void Draw();

private:

	VertexBuffer* m_VertexBuffer;

	Ref<class Shader> m_Shader;
};