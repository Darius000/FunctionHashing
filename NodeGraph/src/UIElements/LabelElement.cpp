#include "PCH.h"
#include "LabelElement.h"

LabelElement::LabelElement(std::string_view name, const std::string& text)
{
	m_Name = name;
	m_Text = text;

	m_Style.m_Color = {1.0f, .5f, 0.0f, 1.0f};
	m_Style.m_Position.right = 100.0f;
	m_Style.m_Position.bottom = 50.0f;
	m_ToolTip = "This tooltip";
	m_Style.m_FontStyle.size.value = 32.0f;
}

void LabelElement::OnDrawElement()
{
	ImGui::TextUnformatted(m_Text.c_str());
}