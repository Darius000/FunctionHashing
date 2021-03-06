#include "Reflection/Reflection.h"
#include "Nodes/CustomEvent.h"

REFLECT_INLINE(CustomEventNode)
{
	rttr::registration::class_<CustomEventNode>("Custom Event")(rttr::metadata("Category", "Events | "), rttr::metadata("Description", "Begin a new Event"))
		.constructor<>()(rttr::policy::ctor::as_raw_ptr);
}