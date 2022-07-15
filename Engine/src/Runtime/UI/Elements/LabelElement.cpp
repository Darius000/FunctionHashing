#include "PCH.h"
#include "LabelElement.h"


LabelElement::LabelElement(std::string_view name, const std::string& text)
	:UIElement(name)
{
	m_Text = text;
}

void LabelElement::OnDrawElement()
{
	ImDrawList* drawlist = ImGui::GetWindowDrawList();

	auto text = m_Binding.IsBound() ? m_Binding.Invoke() : m_Text;

	drawlist->AddText(m_Style.m_FontStyle.font, m_Style.m_FontStyle.size, GetCursorPos() + GetPosition(),
		m_Style.m_FontStyle.color, text.c_str());

	AddElementItem();

	//Debug
	/*ImGui::GetWindowDrawList()->AddRect(
		ImGui::GetItemRectMin(), ImGui::GetItemRectMax(), IM_COL32(255, 0, 180, 255));*/
}

ImRect LabelElement::GetBounds()
{
	float size = m_Style.m_FontStyle.size;
	ImVec2 text_size = m_Style.m_FontStyle.font->CalcTextSizeA(size, FLT_MAX, 0.0f, m_Text.c_str());

	auto max = GetCursorPos() + text_size + GetPosition();
	auto min = GetCursorPos() + GetPosition();
	return ImRect(min, max);
}
