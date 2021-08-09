#pragma once
#include "Node.h"
#include "INodeCreation.h"

class Comment : public Node, public INodeCreation
{

public:
	Comment();

	DEFINE_NODE_CLASS(Comment, "", "Comment")

	//Actual comment string
	std::string m_Comment;
protected:
	void CustomDraw() override;

	void DrawResizeButton();
};