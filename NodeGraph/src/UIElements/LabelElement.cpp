#include "PCH.h"
#include "LabelElement.h"

LabelElement::LabelElement(const std::string& text)
{
	m_Text = text;

	m_Style.m_Color = {1.0f, .5f, 0.0f, 1.0f};
	m_Style.m_Position.right = 100.0f;
	m_Style.m_Position.bottom = 50.0f;
	m_ToolTip = "This tooltip";
	m_Style.m_FontStyle.size.value = 32.0f;
}

void LabelElement::OnDrawElement(ImDrawList* drawlist)
{
	//ImGui::SetNextItemWidth(GetSize().x);
	auto styleHeight = m_Style.m_Position.bottom - m_Style.m_Position.top;
	auto styleWidth = m_Style.m_Position.right - m_Style.m_Position.left;
	auto fontSize = m_Style.m_FontStyle.size.value;

	auto font = m_Style.m_FontStyle.font;
	auto color = ImColor(m_Style.m_FontStyle.color);

	//ImGui::PushClipRect(GetBounds().Min, GetBounds().Max, true);
	
	drawlist->AddText(font, fontSize, GetPosition(), color, m_Text.c_str());
	//ImGui::PopClipRect();
}