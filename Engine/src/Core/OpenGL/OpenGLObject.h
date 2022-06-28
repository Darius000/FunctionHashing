#pragma once

#include "Core/Core.h"


class OpenGLObject
{
public:

	OpenGLObject();

	virtual ~OpenGLObject();

	virtual void Bind() = 0;

	virtual void UnBind() = 0;

protected:

	uint32_t m_RenderID;
};