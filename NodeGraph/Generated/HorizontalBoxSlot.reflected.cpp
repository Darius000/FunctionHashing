#include "Core/Reflection/Reflection.h"
#include "UIElements/Slots/HorizontalBoxSlot.h"
#include "UIElements/Slots/VerticalBoxSlot.h"

REFLECT_INLINE(HorizontalBoxSlot)
{
	registration::class_<HorizontalBoxSlot>("HorizontalBoxSlot")
		.constructor<>()(policy::ctor::as_raw_ptr)
		.property("S_Weight", &HorizontalBoxSlot::m_StartWeight)
		.property("S_Spacing", &HorizontalBoxSlot::m_StartSpacing)
		.property("E_Weight", &HorizontalBoxSlot::m_EndWeight)
		.property("E_Spacing", &HorizontalBoxSlot::m_EndSpacing);
}

REFLECT_INLINE(VerticalBoxSlot)
{
	registration::class_<VerticalBoxSlot>("VerticalBoxSlot")
		.constructor<>()(policy::ctor::as_raw_ptr);
}