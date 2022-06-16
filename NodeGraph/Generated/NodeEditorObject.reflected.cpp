#include "Core/Reflection/Reflection.h"
#include "NodeEditorObject.h"


REFLECT_INLINE(NodeEditorObject)
{
	registration::class_<NodeEditorObject>("NodeEditorObject")(policy::ctor::as_raw_ptr)
		.constructor<>();
}