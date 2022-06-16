#pragma once

#include "Core/Core.h"
#include "DataTypes/Property.h"
#include "LinkableNode.h"
#include "NodeEditorObject.h"

class Node : public LinkableNode
{

public:
	Node();
	virtual ~Node() = default;


	virtual void OnExecute() {};
private:

	REFLECTABLEV(LinkableNode)
};


