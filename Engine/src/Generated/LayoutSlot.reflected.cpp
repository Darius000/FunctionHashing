#include "PCH.h"
#include "Reflection/Reflection.h"
#include "Runtime/UI/Elements/LayoutSlot.h"


REFLECT_INLINE(LayoutSlot)
{
	rttr::registration::class_<LayoutSlot>("LayoutSlot")
		.constructor<>()(rttr::policy::ctor::as_raw_ptr)
		.property("Content", &LayoutSlot::m_Content)
		.property("Parent", &LayoutSlot::m_Parent);
}