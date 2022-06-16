#pragma once

#include "Node.h"

class Comment : public Node
{

public:
	Comment();

	const ENodeType GetNodeType() { return ENodeType::Comment;}

	ImVec4 GetHeaderColor() const override { return { 0.f, 0.f, 0.f, .5f }; }

	ImVec4 GetColor() const override { return {.5f, .5f, .5f, .2f}; }

	//Actual comment string
	std::string m_Comment;

	REFLECTABLEV(Node)
};
