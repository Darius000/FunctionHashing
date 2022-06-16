#include "Core/Reflection/Reflection.h"
#include "Nodes/BaseNode.h"

REFLECT_INLINE(BaseNode)
{
	registration::class_<BaseNode>("BaseNode")(policy::ctor::as_raw_ptr);
}