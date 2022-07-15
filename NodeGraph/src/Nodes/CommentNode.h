#pragma once

#include "Node.h"

class Comment : public Node
{

public:
	Comment();

	ENodeType GetNodeType() { return ENodeType::Comment;}

	Color GetHeaderColor() const override { return { 0.f, 0.f, 0.f, .5f }; }

	Color GetColor() const override { return {.5f, .5f, .5f, .2f}; }

	//Actual comment string
	std::string m_Comment;

	REFLECTABLEV(Node)
};
