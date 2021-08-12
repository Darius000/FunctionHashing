#pragma once

#include "Node.h"
#include "VariableNodeInterface/VariableNodeInterface.h"

template<typename T>
class SetVariableNode : public VariableNodeInterface<T>
{
public:
	SetVariableNode(Ref<IProperty> prop)
		:VariableNodeInterface(prop)
	{
		AddDataPin("In", PropertyType::Input, prop);
		AddDataPin("Out", PropertyType::Output, prop);
		AddExecutionPin(ImNodesAttributeType_Input);
		AddExecutionPin(ImNodesAttributeType_Output);
	}

	virtual void OnExecute() override 
	{
	
	};

	virtual void CustomDraw() override
	{
		ImGui::TextUnformatted(m_Property->GetName().c_str());
	}

	DEFINE_NODE_CLASS(SetVariableNode,"", "", false)

	static Node* CreateMethod(Ref<IProperty> prop) { return new SetVariableNode(prop); }


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