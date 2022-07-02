#pragma once

#include "Core/Core.h"

class RenderObject
{
public:

	virtual ~RenderObject() = default;

	virtual void Bind() {};

	virtual void UnBind() {};

	uint32_t GetRendererID() const { return m_RendererID; }

	operator uint64_t()
	{
		return (uint64_t)m_RendererID;
	}

	operator void* ()
	{
		return &m_RendererID;
	}

protected:

	uint32_t m_RendererID = -1;
};