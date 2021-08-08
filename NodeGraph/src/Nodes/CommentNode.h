#pragma once
#include "Node.h"
#include "INodeCreation.h"

class CommentNode : public Node, public INodeCreation
{

public:
	CommentNode();

	std::string GetTypeName() const override;

	static Node* CreateMethod()
	{
		return new CommentNode();
	}

	static std::string GetFactoryName() { return "Comment"; }

	//Actual comment string
	std::string m_Comment;
protected:
	void CustomDraw() override;

	void DrawResizeButton();
};