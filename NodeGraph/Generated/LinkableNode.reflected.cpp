#include "Core/Reflection/Reflection.h"
#include "Nodes/LinkableNode.h"

REFLECT_INLINE(LinkableNode)
{
	registration::class_<LinkableNode>("LinkableNode")(policy::ctor::as_raw_ptr);
}