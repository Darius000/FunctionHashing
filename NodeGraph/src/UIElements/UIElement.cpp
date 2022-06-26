#include "UIElement.h"
#include "Layouts/Layouts.h"


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

	if (m_Interactive == false) return;

	//handles events from bottom to top
	HandleEvents();

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
	return ImVec2(m_Style.m_Position.left, m_Style.m_Position.top);
}

ImVec2 UIElement::GetSize() 
{
	return ImVec2(m_Style.m_Position.right, m_Style.m_Position.bottom);
}

ImRect UIElement::GetBounds() 
{
	auto position = GetPosition();
	auto size = GetSize();
	return ImRect(position.x, position.y, size.x, size.y);
}

void UIElement::SetPosition(const ImVec2& pos)
{
	m_Style.m_Position.left = pos.x;
	m_Style.m_Position.top = pos.y;
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

bool UIElement::HandleEvents()
{
	return false;
}
