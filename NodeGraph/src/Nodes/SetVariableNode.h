#pragma once

#include "Node.h"
#include "GetVariableNode.h"
#include "DataTypes/Property.h"
#include "INodeCreation.h"

template<typename T>
class SetVariableNode : public Node, public INodeCreation
{
public:
	SetVariableNode(Ref<IProperty> prop)
	{
		m_PropertyName = prop->GetName();
		prop->AddRef(GetID());

		AddDataPin<T>("In", ImNodesAttributeType_Input, prop);
		AddDataPin<T>("Out", ImNodesAttributeType_Output, prop);
		AddExecutionPin(ImNodesAttributeType_Input);
		AddExecutionPin(ImNodesAttributeType_Output);

		m_Color = prop->GetColor();
		m_Color.w = .5f;
		m_TitleStyle = ETitleStyle_::Custom;
	}

	virtual void OnExecute() override 
	{
	
	};

	virtual void CustomDraw() override
	{
		auto propdata = GetParameter("Out");
		ImGui::TextUnformatted(propdata->GetProperty()->GetName().c_str());
	}

	static std::string GetFactoryName();

	static Node* CreateMethod(Ref<IProperty> prop)
	{
		return new SetVariableNode(prop);
	}

	std::string m_PropertyName;

	std::string GetTypeName() const override
	{
		return "Set";
	}
};

template<>
std::string SetVariableNode<int>::GetFactoryName()
{
	return "Setint";
}


template<>
std::string SetVariableNode<float>::GetFactoryName()
{
	return "Setfloat";
}


template<>
std::string SetVariableNode<bool>::GetFactoryName()
{
	return "Setbool";
}