#pragma once

#include "Node.h"

class If_ElseNode :public Node
{
public:
	If_ElseNode();

	void OnExecute() override;

	Color GetHeaderColor() const override { return { 1.0f, 0.0f, 0.0f, 1.0f }; }

	bool m_InCondition;

	REFLECTABLEV(Node)
};

