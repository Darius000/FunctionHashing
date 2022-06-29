#include "PCH.h"
#include "Reflection/Reflection.h"
#include "Runtime/UI/Elements/UIElement.h"
#include "Runtime/UI/Elements/LayoutSlot.h"

REFLECT_INLINE(UIElementStyle)
{
	rttr::registration::class_<UIElementStyle>("UIElementStyle")
	.property("Position", &UIElementStyle::m_Position)
	.property("Size", &UIElementStyle::m_Size)
	.property("Color", &UIElementStyle::m_Color)
	.property("Hovered Style", &UIElementStyle::hoveredStyle)
	.property("Font Style", &UIElementStyle::m_FontStyle)
	.property("Tool Tip Style", &UIElementStyle::m_ToolTipStyle)
	.property("Border Radius", &UIElementStyle::m_BorderRadius)
	.property("Border Width", &UIElementStyle::m_BorderWidth)
	.property("Border Color", &UIElementStyle::m_BorderColor);
}

REFLECT_INLINE(UIElement)
{
	rttr::registration::class_<UIElement>("UIElement")
		.constructor<>()(rttr::policy::ctor::as_raw_ptr)
		.property("Interactive", &UIElement::m_Interactive)
		.property("Enabled", &UIElement::m_Enabled)
		.property("Style", &UIElement::m_Style);
}