#pragma once

#include "RenderObject.h"
#include "BufferLayout.h"

class VertexBuffer : public RenderObject
{
public:

	virtual ~VertexBuffer() = default;

	virtual void SetData(const void* data, uint32_t size) = 0;

	virtual const BufferLayout& GetLayout() const = 0;

	virtual void SetLayout(const BufferLayout& layout) = 0;

	static Ref<VertexBuffer> Create(uint32_t size);
	static Ref<VertexBuffer> Create(float* vertices, uint32_t size);
};
