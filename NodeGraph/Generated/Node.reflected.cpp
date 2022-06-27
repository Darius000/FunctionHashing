#include "Core/Reflection/Reflection.h"
#include "Nodes/Node.h"

REFLECT_INLINE(Node)
{
	rttr::registration::class_<Node>("Node")(rttr::policy::ctor::as_raw_ptr);
}