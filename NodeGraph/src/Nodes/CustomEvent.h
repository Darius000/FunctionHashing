#pragma once


#include "Node.h"

#define TYPENAME "CustomEvent"

class CustomEventNode : public Node
{
public:
	CustomEventNode();

	DEFINE_NODE_CLASS(CustomEventNode, "", "Add An Event", true)


	static Node* CreateMethod()
	{
		return new CustomEventNode();
	}
};

#undef TYPENAME