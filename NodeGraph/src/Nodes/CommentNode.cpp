#include "PCH.h"
#include "CommentNode.h"
#include "NodeGraph/NodeGraph.h"

Comment::Comment()
{
	m_Comment = "This is a comment node!";
	m_Color = {.1f, .1f, .1f , .2f};
	m_Size = ImVec2(100, 100);
}

DEFINE_REGISTER_NODE(Comment)