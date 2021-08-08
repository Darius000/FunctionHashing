#pragma once

#include "Core/Core.h"
#include "FunctionNode.h"
#include "INodeCreation.h"

class If_ElseNode :public FunctionNode, public INodeCreation
{
public:
	If_ElseNode();

	void OnExecute() override;

	virtual std::string GetTypeName() const override { return "If_Else";};

	static Node* CreateMethod()
	{
		return new If_ElseNode();
	}

	static std::string GetFactoryName() { return "If Else"; }

	bool default_in = false;
};	

