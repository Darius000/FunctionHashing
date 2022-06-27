#pragma once


#include "Node.h"

class CustomEventNode : public Node
{
public:
	CustomEventNode();

	Color GetHeaderColor() const override { return { 1.0f, .4f, .4f, 1.0f }; }

	REFLECTABLEV(Node)
};
