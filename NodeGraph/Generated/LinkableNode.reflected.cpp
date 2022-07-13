#include "Reflection/Reflection.h"
#include "Nodes/LinkableNode.h"

REFLECT_INLINE(LinkableNode)
{
	rttr::registration::class_<LinkableNode>("LinkableNode")
		.constructor<>()(rttr::policy::ctor::as_raw_ptr);
}