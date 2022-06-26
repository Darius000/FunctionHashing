#include "LabelElement.h"

LabelElement::LabelElement(std::string_view name, const std::string& text)
	:UIElement(name)
{
	m_Text = text;

	m_Style.m_Position.right = 100.0f;
	m_Style.m_Position.bottom = 50.0f;
	m_ToolTip = "This tooltip";
}

void LabelElement::OnDrawElement()
{
	ImDrawList* drawlist = ImGui::GetWindowDrawList();


	drawlist->AddText(m_Style.m_FontStyle.font, m_Style.m_FontStyle.size.value, GetCursorPos() + GetPosition(),
		m_Style.m_FontStyle.color, m_Text.c_str());

	AddElementItem();

	//Debug
	/*ImGui::GetWindowDrawList()->AddRect(
		ImGui::GetItemRectMin(), ImGui::GetItemRectMax(), IM_COL32(255, 0, 0, 255));*/
}

ImRect LabelElement::GetBounds()
{
	float size = m_Style.m_FontStyle.size.value;
	ImVec2 text_size = m_Style.m_FontStyle.font->CalcTextSizeA(size, FLT_MAX, 0.0f, m_Text.c_str());

	auto max = GetCursorPos() + text_size;
	auto min = GetCursorPos() + GetPosition();
	return ImRect(min, max);
}
