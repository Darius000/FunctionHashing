#include "Core/Reflection/Reflection.h"
#include "Nodes/BaseNode.h"

REFLECT_INLINE(BaseNode)
{
	rttr::registration::class_<BaseNode>("BaseNode")(rttr::policy::ctor::as_raw_ptr);
}