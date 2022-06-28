#pragma once

#include "OpenGLObject.h"

class IndexBuffer : public OpenGLObject
{
public:

	IndexBuffer(uint32_t* indices, uint32_t count);

	~IndexBuffer();

	void Bind() override;

	void UnBind() override;

	uint32_t GetCount() const { return m_Count; }

	static Ref<IndexBuffer> Create(uint32_t* indices, uint32_t count);

private:
	uint32_t m_Count;
};