#include "PCH.h"
#include "UIElement.h"
#include "Core/Helpers/Vectors/VectorHelper.h"


UIElement::UIElement()
{

}

UIElement::~UIElement()
{

}

void UIElement::DrawElement()
{
	if (m_Enabled == false) return;

	OnBeginDraw();

	for (auto child : GetChildren())
	{
		child->DrawElement();
	}

	OnDrawElement();

	OnEndDraw();

	bool handled = false;
	for (auto child : GetChildren())
	{
		handled |= child->HandleEvents();
		if (handled)
		{
			break;
		}
	}

	if (!handled)
	{
		HandleEvents();
	}
}

void UIElement::AddChild(UIElement* element)
{
	element->m_ParentElement = this;

	m_Children.push_back(Ref<UIElement>(element));
}

void UIElement::RemoveElement(UIElement* element)
{
	Helpers::Vector::Remove(m_Children, Ref<UIElement>(element));
	
	element->m_ParentElement = nullptr;
}

void UIElement::RemoveElement(const std::string& name)
{
	auto element = Helpers::Vector::FindPred(m_Children, [&](Ref<UIElement>& element) {
		return element->m_Name == name;
		});

	Helpers::Vector::Remove(m_Children, element);

	element->m_ParentElement = nullptr;
}

void UIElement::Clear()
{
	m_Children.clear();
}

ImVec2 UIElement::GetPosition() 
{
	return m_ParentElement ? m_ParentElement->GetPosition() + GetLocalPosition() : GetLocalPosition();
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

void UIElement::AddElementItem(const ImRect& bounds, ImGuiID id)
{
	ImGui::PushID(id);
	ImGui::PushClipRect(bounds.Min, bounds.Max, false);
	ImGui::ItemAdd(bounds, id);
	ImGui::ItemSize(bounds);
	ImGui::PopClipRect();
	ImGui::PopID();
}

bool UIElement::HandleEvents()
{
	return false;
}
