#pragma once


#include "VertexArray.h"

class RendererAPI
{
public:
	enum class API
	{
		None, Opengl, Vulkan, Directx
	};

	virtual ~RendererAPI() = default;

	virtual void Init() = 0;
	virtual void SetClearColor(const glm::vec4& color) = 0;
	virtual void Clear() = 0;
	virtual void Flush() = 0;

	virtual void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexcount = 0) = 0;

	virtual void SetLineWidth(float width) = 0;

	static API GetAPI() { return s_API;  }
	static Scope<RendererAPI> Create();

private:

	static API s_API;
};