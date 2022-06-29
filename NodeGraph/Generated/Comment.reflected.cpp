#include "Reflection/Reflection.h"
#include "Nodes/CommentNode.h"

REFLECT_INLINE(Comment)
{
	rttr::registration::class_<Comment>("Comment")(rttr::metadata("Category", "Comments | "), rttr::metadata("Description", "Adds a new comment node"))
		.constructor<>()(rttr::policy::ctor::as_raw_ptr)
		.property("Message", &Comment::m_Comment)(rttr::metadata("Kind", "Input"));
}