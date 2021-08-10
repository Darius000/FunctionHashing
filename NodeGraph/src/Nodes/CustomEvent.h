#pragma once


#include "Node.h"

class CustomEventNode : public Node
{
public:
	CustomEventNode();

	DEFINE_NODE_CLASS(CustomEventNode, "", "Add An Event", true)

	static Node* CreateMethod()
	{
		return new CustomEventNode();
	}

	virtual void CustomDraw() override;

	virtual void OnExecute() override;
};