#include "PCH.h"
#include "Shader.h"
#include "RendererAPI.h"
#include "OpenGL/OpenGLShader.h"

Ref<Shader> Shader::Create(const std::string& filename)
{
	switch (RendererAPI::GetAPI())
	{
	case RendererAPI::API::Opengl:
			return MakeRef<OpenGLShader>(filename);
	}

	return nullptr;
}

Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
{
	switch (RendererAPI::GetAPI())
	{
	case RendererAPI::API::Opengl:
		return MakeRef<OpenGLShader>(name, vertexSrc, fragmentSrc);
	}

	return nullptr;
}
