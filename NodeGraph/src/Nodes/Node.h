#pragma once

#include "LinkableNode.h"

class Node : public LinkableNode
{

public:
	Node();
	virtual ~Node() = default;


	virtual void OnExecute() {};
private:

	REFLECTABLEV(LinkableNode)
};


