#pragma once

#include "Core/Core.h"
#include "Node.h"

#define TYPENAME "Branch"

class If_ElseNode :public Node
{
public:
	If_ElseNode();

	void OnExecute() override;

	DEFINE_NODE_CLASS(If_ElseNode, "", "Branching", true);

	static Node* CreateMethod() { return new If_ElseNode(); }
};	

#undef TYPENAME