#pragma once

#include "Renderer/IndexBuffer.h"

class OpenGlIndexBuffer : public IndexBuffer
{
public:

	OpenGlIndexBuffer(uint32_t* indices, uint32_t count);

	~OpenGlIndexBuffer();

	void Bind() override;

	void UnBind() override;

	uint32_t GetCount() const override { return m_Count; }

private:
	uint32_t m_Count;
};