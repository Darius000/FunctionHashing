#pragma once

#include "Nodes/Node.h"


template<typename T>
class VariableNodeInterface : public Node
{
public:
	VariableNodeInterface(Ref<struct IProperty> prop)
		:m_Property(prop)
	{
		
		m_TitleStyle = ETitleStyle_::Custom;

		m_PropertyName = prop->GetName();
		m_Property->AddRef(GetID());
		m_Color = prop->GetColor();
		m_Color.w = .5f;
	}

	Ref<struct IProperty> m_Property;
	std::string m_PropertyName;
};