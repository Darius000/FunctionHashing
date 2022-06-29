#pragma once

#include "Core/UUID.h"

class Edge
{
public:

	Edge(Core::UUID start, Core::UUID end)
		:m_StartID(start), m_EndID(end)
	{

	}

	inline std::pair<Core::UUID, Core::UUID> GetIds() { return std::make_pair(m_StartID, m_EndID); }

private:
	Core::UUID m_StartID;

	Core::UUID m_EndID;
};