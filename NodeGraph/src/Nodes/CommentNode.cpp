#include "PCH.h"
#include "CommentNode.h"
#include "NodeGraph/NodeGraph.h"

Comment::Comment()
{
	m_Name = "Comment";
	m_Comment = "This is a comment node!";
}

RTTR_REGISTRATION
{
	registration::class_<Comment>("Comment")(metadata("Category", "Comments | "), metadata("Description", "Adds a new comment node"))
		.constructor<>()(policy::ctor::as_raw_ptr)
		.property("Message", &Comment::m_Comment);
}