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
		
	}

	virtual void OnExecute() override 
	{
	
	};

};
