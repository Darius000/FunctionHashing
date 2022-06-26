#include "Core/Reflection/Reflection.h"
#include "UIElements/Slots/LayoutSlot.h"


REFLECT_INLINE(LayoutSlot)
{
	registration::class_<LayoutSlot>("LayoutSlot")
		.constructor<>()(policy::ctor::as_raw_ptr)
		.property("Content", &LayoutSlot::m_Content)
		.property("Parent", &LayoutSlot::m_Parent);
}