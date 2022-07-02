#pragma once


#include "RenderObject.h"

class IndexBuffer : public RenderObject
{
public:

	virtual ~IndexBuffer() = default;

	virtual uint32_t GetCount() const = 0;

	static Ref<IndexBuffer> Create(uint32_t* indices, uint32_t count);
};