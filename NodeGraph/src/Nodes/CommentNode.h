#pragma once

#include "Node.h"

class Comment : public Node
{

public:
	Comment();

	DEFINE_NODE_CLASS(Comment, "", "Comment", true)

	static Node* CreateMethod() { return new Comment(); }

	//Actual comment string
	std::string m_Comment;
protected:
	void CustomDraw() override;
	void OnDrawDetails() override;

	void DrawResizeButton();
};