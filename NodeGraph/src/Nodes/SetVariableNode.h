#pragma once

#include "Node.h"
#include "VariableNodeInterface/VariableNodeInterface.h"

#define TYPENAME "Set"

template<typename T>
class SetVariableNode : public VariableNodeInterface<T>
{
public:
	SetVariableNode(Ref<IProperty> prop)
		:VariableNodeInterface(prop)
	{
		
	}

	virtual void OnExecute() override 
	{
	
	};

	DEFINE_NODE_CLASS(SetVariableNode,"", "", false)

	static Node* CreateMethod(Ref<IProperty> prop) { return new SetVariableNode(prop); }


};

#undef TYPENAME

template<>
std::string SetVariableNode<int>::GetStaticFactoryName()
{
	return "Setint";
}


template<>
std::string SetVariableNode<float>::GetStaticFactoryName()
{
	return "Setfloat";
}


template<>
std::string SetVariableNode<bool>::GetStaticFactoryName()
{
	return "Setbool";
}