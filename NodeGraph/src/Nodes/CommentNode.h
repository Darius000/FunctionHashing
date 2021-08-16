#pragma once

#include "Node.h"

#define TYPENAME "Comment"

class Comment : public Node
{

public:
	Comment();

	DEFINE_NODE_CLASS(Comment, "", "Comment", true)

	static Node* CreateMethod() { return new Comment(); }

	const ENodeType GetNodeType() { return ENodeType::Comment;}

	//Actual comment string
	std::string m_Comment;

	ImVec2 m_Size;
};

#undef TYPENAME