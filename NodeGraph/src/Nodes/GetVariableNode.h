#pragma once 

#include "VariableNodeInterface/VariableNodeInterface.h"

template<typename T>
class GetVariableNode : public VariableNodeInterface<T>
{
public:
	GetVariableNode(Ref<IProperty> prop)
		:VariableNodeInterface(prop)
	{
	}
	

protected:
};

