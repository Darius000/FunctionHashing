#pragma once


#include "Node.h"

class CustomEventNode : public Node
{
public:
	CustomEventNode();

	ImVec4 GetHeaderColor() const override { return { 1.0f, .4f, .4f, 1.0f }; }

	RTTR_ENABLE(Node)
};
