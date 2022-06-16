#include "Core/Reflection/Reflection.h"
#include "Nodes/Node.h"

REFLECT_INLINE(Node)
{
	registration::class_<Node>("Node")(policy::ctor::as_raw_ptr);
}