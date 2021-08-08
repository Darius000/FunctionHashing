#pragma once

#include "Node.h"
#include "INodeCreation.h"

template<typename T>
class GetVariableNode : public Node
{
public:
	GetVariableNode(Ref<IProperty> prop)
	{
		m_PropertyName = prop->GetName();
		prop->AddRef(GetID());

		AddDataPin<T>(m_PropertyName, ImNodesAttributeType_Output, prop);

		m_Color = prop->GetColor();
		m_Color.w = .5f;
		m_TitleStyle = ETitleStyle_::Custom;
	}

	std::string GetTypeName() const override
	{
		return "Get";
	}

	static std::string GetFactoryName();

	static Node* CreateMethod(Ref<IProperty> prop)
	{
		return new GetVariableNode(prop);
	}

	std::string m_PropertyName;
protected:
	void CustomDraw() override
	{
		auto propdata = GetParameter(0);

		ImGui::TextUnformatted(propdata->GetProperty()->GetName().c_str());
	}
};

template<>
inline std::string GetVariableNode<int>::GetFactoryName()
{
	return "Getint";
}


template<>
inline std::string GetVariableNode<float>::GetFactoryName()
{
	return "Getfloat";
}


template<>
inline std::string GetVariableNode<bool>::GetFactoryName()
{
	return "Getbool";
}
