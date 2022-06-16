#include "Core/Reflection/Reflection.h"
#include "Nodes/CustomEvent.h"

REFLECT_INLINE(CustomEventNode)
{
	registration::class_<CustomEventNode>("CustomEvent")(metadata("Category", "Events | "), metadata("Description", "Begin a new Event"))
		.constructor<>()(policy::ctor::as_raw_ptr);
}