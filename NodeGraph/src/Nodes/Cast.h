#pragma once

#include "Node.h"

template<typename From, typename To>
class CastTo : public Node
{
public:
	CastTo() 
	{
		m_Name = std::string("Cast ") + rttr::type::get<From>().get_name().to_string() + " to " + rttr::type::get<To>().get_name().to_string();
	}

	virtual const ENodeType GetNodeType() override { return ENodeType::Simple; }

	RTTR_ENABLE(Node)
};