#pragma once

#include "DataTypes/DataTypeEnum.h"
#include "Nodes/Node.h"

enum class EVariableNodeType : uint8_t
{
	Get,
	Set,
	Max
};


template<>
std::vector<std::string> EnumStrings<EVariableNodeType>::Data = {
		"Get", "Set"
};


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