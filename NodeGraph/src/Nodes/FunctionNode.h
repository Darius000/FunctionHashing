#pragma once

#include "Node.h"

class FunctionNode : public Node
{
public:
	FunctionNode();

protected:

	//if true show title on node instead
	bool m_Compact = false;

	bool m_Variable = false;
};
