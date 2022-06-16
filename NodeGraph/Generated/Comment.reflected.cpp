#include "Core/Reflection/Reflection.h"
#include "Nodes/CommentNode.h"

REFLECT_INLINE(Comment)
{
	registration::class_<Comment>("Comment")(metadata("Category", "Comments | "), metadata("Description", "Adds a new comment node"))
		.constructor<>()(policy::ctor::as_raw_ptr)
		.property("Message", &Comment::m_Comment)(metadata("Kind", "Input"));
}