#pragma once

#include "Core/Core.h"
#include "Renderer/Shader.h"
#include <glad/glad.h>

class OpenGLShader : public Shader
{
public:

	OpenGLShader(const std::string& filepath);
	OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);

	~OpenGLShader();

	void Bind() override;
	void UnBind() override;

	void SetInt(const std::string& name, int value);
	void SetIntArray(const std::string& name, int* values, uint32_t count);
	void SetFloat(const std::string& name, float value);
	void SetFloat2(const std::string& name, const glm::vec2& value);
	void SetFloat3(const std::string& name, const glm::vec3& value);
	void SetFloat4(const std::string& name, const glm::vec4& value);
	void SetMat3(const std::string& name, const glm::mat3& value);
	void SetMat4(const std::string& name, const glm::mat4& value);
	void SetBool(const std::string& name, bool value);

	const std::string& GetName() const { return m_Name; }

private:
	std::string ReadFile(const std::string& filepath);
	std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
	void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);

	GLint GetUniformLocation(const std::string& name);
private:

	std::string m_Name;
};