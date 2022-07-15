#include "PCH.h"
#include "Reflection/Reflection.h"
#include "Runtime/UI/Elements/HorizontalBoxSlot.h"
#include "Runtime/UI/Elements/VerticalBoxSlot.h"

REFLECT_INLINE(HorizontalBoxSlot)
{
	rttr::registration::class_<HorizontalBoxSlot>("HorizontalBoxSlot")
		.constructor<>()(rttr::policy::ctor::as_raw_ptr)
		.constructor<const LayoutConfig&>()(rttr::policy::ctor::as_raw_ptr)
		.property("Configuration", &HorizontalBoxSlot::m_Configuration);
}

REFLECT_INLINE(VerticalBoxSlot)
{
	rttr::registration::class_<VerticalBoxSlot>("VerticalBoxSlot")
		.constructor<>()(rttr::policy::ctor::as_raw_ptr)
		.constructor<const LayoutConfig&>()(rttr::policy::ctor::as_raw_ptr)
		.property("Configuration", &HorizontalBoxSlot::m_Configuration);
}