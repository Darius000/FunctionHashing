#include "PCH.h"
#include "Reflection/Reflection.h"
#include "HorizontalBoxSlot.h"
#include "VerticalBoxSlot.h"

REFLECT_INLINE(HorizontalBoxSlot)
{
	rttr::registration::class_<HorizontalBoxSlot>("HorizontalBoxSlot")
		.constructor<>()(rttr::policy::ctor::as_raw_ptr)
		.property("S_Weight", &HorizontalBoxSlot::m_StartWeight)
		.property("S_Spacing", &HorizontalBoxSlot::m_StartSpacing)
		.property("E_Weight", &HorizontalBoxSlot::m_EndWeight)
		.property("E_Spacing", &HorizontalBoxSlot::m_EndSpacing);
}

REFLECT_INLINE(VerticalBoxSlot)
{
	rttr::registration::class_<VerticalBoxSlot>("VerticalBoxSlot")
		.constructor<>()(rttr::policy::ctor::as_raw_ptr);
}