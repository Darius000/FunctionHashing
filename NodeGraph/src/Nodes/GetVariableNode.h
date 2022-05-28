#pragma once 

#include "VariableNodeInterface/VariableNodeInterface.h"
#include "INodeCreation.h"

#define TYPENAME "Get"

template<typename T>
class GetVariableNode : public VariableNodeInterface<T>
{
public:
	GetVariableNode(Ref<IProperty> prop)
		:VariableNodeInterface(prop)
	{
		m_Rounding = 30.0f;
	
		
	}
	
	DEFINE_NODE_CLASS(GetVariableNode, "", "", false)

	static Node* CreateMethod(Ref<IProperty> prop)
	{
		return new GetVariableNode(prop);
	}

protected:
};

#undef TYPENAME

template<>
inline std::string GetVariableNode<int>::GetStaticFactoryName() 
{
	return "Getint";
}


template<>
inline std::string GetVariableNode<float>::GetStaticFactoryName() 
{
	return "Getfloat";
}


template<>
inline std::string GetVariableNode<bool>::GetStaticFactoryName() 
{
	return "Getbool";
}
