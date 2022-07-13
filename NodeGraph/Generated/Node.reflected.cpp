#include "Reflection/Reflection.h"
#include "Nodes/Node.h"

REFLECT_INLINE(Node)
{
	rttr::registration::class_<Node>("Node")
		.constructor<>()(rttr::policy::ctor::as_raw_ptr);
}