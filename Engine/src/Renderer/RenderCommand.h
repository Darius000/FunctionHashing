#pragma once


#include "RendererAPI.h"

class RenderCommand
{
public :

	static void Init()
	{
		s_RendererAPI->Init();
	};

	static void SetClearColor(const glm::vec4& color)
	{
		s_RendererAPI->SetClearColor(color);
	}

	static void Clear()
	{
		s_RendererAPI->Clear();
	}

	static void Flush()
	{
		s_RendererAPI->Flush();
	}

	static void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray, uint32_t indexcount = 0)
	{
		s_RendererAPI->DrawIndexed(vertexArray, indexcount);
	}

	static void SetLineWidth(float width)
	{
		s_RendererAPI->SetLineWidth(width);
	}

private:

	static Scope<RendererAPI> s_RendererAPI;
};