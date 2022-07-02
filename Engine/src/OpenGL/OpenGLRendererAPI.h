#pragma once

#include "Core/Core.h"
#include "Renderer/RendererAPI.h"

class OpenGLRendererAPI : public RendererAPI
{
public:
	virtual void Init() override;
	virtual void SetClearColor(const glm::vec4& color) override;
	virtual void Clear() override;
	virtual void Flush() override;

	virtual void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexcount) override;

	virtual void SetLineWidth(float width) override;
};