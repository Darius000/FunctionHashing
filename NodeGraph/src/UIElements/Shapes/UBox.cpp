#include "UBox.h"

UBox::UBox()
{
}

void UBox::OnDrawElement()
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	ImDrawList* drawlist = window->DrawList;

	auto pos = GetCursorPos();
	auto style = GetStyle();
	auto bounds = GetBounds();

	
	if (m_BoxStyle.m_Filled)
	{
		drawlist->AddRectFilled(bounds.Min, bounds.Max, style.m_Color, m_BoxStyle.m_Rounding, m_BoxStyle.GetRoundingFlags());
	}
	else
	{
		drawlist->AddRect(bounds.Min, bounds.Max, style.m_Color, m_BoxStyle.m_Rounding, m_BoxStyle.GetRoundingFlags(), m_BoxStyle.m_Thickness);
	}

	AddElementItem();
}

ImRect UBox::GetBounds()
{
	return UIElement::GetBounds();
}
