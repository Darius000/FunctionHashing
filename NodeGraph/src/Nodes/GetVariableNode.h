#pragma once

#include "VariableNodeInterface/VariableNodeInterface.h"
#include "INodeCreation.h"

template<typename T>
class GetVariableNode : public VariableNodeInterface<T>
{
public:
	GetVariableNode(Ref<IProperty> prop)
		:VariableNodeInterface(prop)
	{
		AddDataPin<T>(m_PropertyName, ImNodesAttributeType_Output, prop);
	}
	
	DEFINE_NODE_CLASS(GetVariableNode, "", "", false)

	static Node* CreateMethod(Ref<IProperty> prop)
	{
		return new GetVariableNode(prop);
	}

	std::string m_PropertyName;
protected:
	void CustomDraw() override
	{
		ImGui::TextUnformatted(m_Property->GetName().c_str());
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
