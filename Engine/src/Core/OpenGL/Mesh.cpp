#include "PCH.h"
#include "Mesh.h"
#include <glad/glad.h>

Mesh::Mesh()
{
	m_Shader = MakeRef<Shader>("resources/Texture.glsl");
}

void Mesh::Draw()
{
	//glDrawElements(GL_TRIANGLES, , GL_UNSIGNED_INT, );
}
