#include "PCH.h"
#include "Reflection/Reflection.h"
#include "Types/Color.h"

REFLECT_INLINE(Color)
{
	rttr::registration::class_<Color>("Color")
		.constructor<>()(rttr::policy::ctor::as_object)
		.constructor<float, float, float, float>()(rttr::policy::ctor::as_object)
		.constructor<const ImVec4&>()(rttr::policy::ctor::as_object)
		.constructor<const ImColor&>()(rttr::policy::ctor::as_object);
}