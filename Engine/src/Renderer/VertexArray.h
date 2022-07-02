#pragma once

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include <vector>

class VertexArray : public RenderObject
{
public:

	virtual ~VertexArray() = default;

	virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) = 0;
	virtual void SetIndexBuffer(const  Ref<IndexBuffer> &indexBuffer) = 0;

	virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const = 0;
	virtual const Ref<IndexBuffer>& GetIndexBuffer() const = 0;


	static Ref<VertexArray> Create();
};

