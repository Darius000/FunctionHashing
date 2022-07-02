#pragma once

#include "RenderObject.h"

class Shader : public RenderObject
{
public:

	virtual ~Shader() = default;

	virtual void SetInt(const std::string& name, int value) = 0;
	virtual void SetIntArray(const std::string& name, int* values, uint32_t count) = 0;
	virtual void SetFloat(const std::string& name, float value) = 0;
	virtual void SetFloat2(const std::string& name, const glm::vec2& value) = 0;
	virtual void SetFloat3(const std::string& name, const glm::vec3& value) = 0;
	virtual void SetFloat4(const std::string& name, const glm::vec4& value) = 0;
	virtual void SetMat3(const std::string& name, const glm::mat3& value) = 0;
	virtual void SetMat4(const std::string& name, const glm::mat4& value) = 0;
	virtual void SetBool(const std::string& name, bool value) = 0;

	virtual const std::string& GetName() const = 0;

	static Ref<Shader> Create(const std::string& filename);
	static Ref<Shader> Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
};