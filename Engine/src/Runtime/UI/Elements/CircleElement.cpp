#include "PCH.h"
#include "CircleElement.h"

CircleElement::CircleElement(std::string_view name)
	:UIElement(name)
{
}

void CircleElement::OnDrawElement()
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	ImDrawList* drawlist = window->DrawList;

	auto pos = GetCursorPos();
	auto style = GetStyle();
	auto circle_style = m_CircleStyle;
	auto bounds = GetBounds();
	auto center = ImVec2(pos.x + GetPosition().x , pos.y + m_CircleStyle.m_Radius + m_CircleStyle.m_Thickness * .5f);

	if (drawlist)
	{
		if (circle_style.m_Filled)
		{
			drawlist->AddCircleFilled(center, m_CircleStyle.m_Radius, style.m_Color, circle_style.m_Resolution);
		}
		else
		{
			drawlist->AddCircle(center, m_CircleStyle.m_Radius, style.m_Color, circle_style.m_Resolution, circle_style.m_Thickness);
		}
	}

	AddElementItem();

	//Debug
	/*ImGui::GetWindowDrawList()->AddRect(
		ImGui::GetItemRectMin(), ImGui::GetItemRectMax(), IM_COL32(255, 0, 0, 255));*/


}

ImRect CircleElement::GetBounds()
{
	auto pos = GetCursorPos();
	pos = ImVec2(pos.x + GetPosition().x, pos.y + m_CircleStyle.m_Radius + m_CircleStyle.m_Thickness * .5f);
	float offset = m_CircleStyle.m_Radius + m_CircleStyle.m_Thickness * .5f;
	return ImRect(pos - ImVec2(offset, offset), pos + ImVec2(offset, offset));
}
