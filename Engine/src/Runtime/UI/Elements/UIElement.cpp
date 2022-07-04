#include "PCH.h"
#include "UIElement.h"
#include "Layouts.h"


UIElement::UIElement()
{

}

UIElement::UIElement(std::string_view name)
{
	m_Name = name;
}

UIElement::~UIElement()
{

}

void UIElement::DrawElement()
{
	if (m_Enabled == false) return;

	ImGui::PushID((uint32_t)GetID());

	//OnBeginDraw();

	OnDrawElement();

	//OnEndDraw();

	ImGui::PopID();
}

void UIElement::OnDrawElement()
{
	
}

ImVec2 UIElement::GetPosition() 
{
	return GetParent() ? GetParent()->GetPosition() + GetLocalPosition() : GetLocalPosition();
}

ImVec2 UIElement::GetLocalPosition()
{
	return m_Style.m_Position;
}

ImVec2 UIElement::GetSize() 
{
	return m_Style.m_Size;
}

ImRect UIElement::GetBounds() 
{
	auto position = GetPosition();
	auto size = GetSize();
	return ImRect(position, position + size);
}

void UIElement::SetPosition(const ImVec2& pos)
{
	m_Style.m_Position = pos;
}

LayoutElement* UIElement::GetParent()
{
	if (m_ParentSlot)
	{
		return m_ParentSlot->m_Parent.get();
	}

	return nullptr;
}

ImVec2 UIElement::GetCursorPos()
{
	auto window = ImGui::GetCurrentWindow();
	
	return ImVec2(window->DC.CursorPos.x, window->DC.CursorPos.y + window->DC.CurrLineTextBaseOffset);
}

void UIElement::AddElementItem()
{
	auto id = (uint32_t)GetID();
	auto bounds = GetBounds();

	
	//ImGui::PushClipRect(bounds.Min, bounds.Max, false);
	ImGui::ItemAdd(bounds, id, 0);
	ImGui::ItemSize(bounds, 0);
	//ImGui::PopClipRect();
}
