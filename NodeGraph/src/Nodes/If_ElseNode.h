#pragma once

#include "Core/Core.h"
#include "FunctionNode.h"
#include "INodeCreation.h"

class If_ElseNode :public FunctionNode, public INodeCreation
{
public:
	If_ElseNode();

	void OnExecute() override;

	DEFINE_NODE_CLASS(If_ElseNode, "", "Branching");

	bool default_in = false;
};	

