#include "PCH.h"
#include "UIElement.h"
#include "Core/Helpers/Vectors/VectorHelper.h"


UIElement::UIElement()
{

}

UIElement::~UIElement()
{

}

void UIElement::DrawElement(ImDrawList* drawlist)
{

	ImGuiWindow* window = ImGui::GetCurrentWindow();
	if (window->SkipItems || !m_Enabled)
		return;

	//colors
	ImColor bgColor = !m_Hovered ? (ImVec4)m_Style.m_Color : (ImVec4)m_Style.hoveredStyle.color;
	ImColor borderColor = (ImVec4)m_Style.m_BorderColor;
	auto minbb = GetBounds().Min;
	auto maxbb = GetBounds().Max;

	//draw background
	drawlist->AddRectFilled(minbb, maxbb, bgColor, m_Style.m_BorderRadius.value);

	//draw border
	if (m_Style.m_BorderWidth.value > 0.0f)
	{
		drawlist->AddRect(minbb, maxbb, borderColor, m_Style.m_BorderRadius.value, ImDrawCornerFlags_All, m_Style.m_BorderWidth.value);
	}

	//draw foreground
	OnDrawElement(drawlist);

	//draw children

	{
		for (auto it = m_Children.rbegin(); it != m_Children.rend();)
		{
			if (*it)
			{
				
				(*it)->DrawElement(drawlist);
			}

			it++;
		}
	}

	auto id = GetID();
	auto bb = GetBounds();

	AddElementItem(bb, id);

	//handle events starting from top most to bottom 
	{
		auto handled = false;
		for (auto it = m_Children.end(); it != m_Children.begin();)
		{
			handled = (*--it)->HandleEvents();
			if (handled)
			{
				break;
			}
		}

		if (!handled)
			HandleEvents();
	}

	if (m_Hovered && ImGui::GetHoveredID() == GetID())
	{
		DrawToolTip();
	}
}

void UIElement::OnDrawElement(ImDrawList* drawlist)
{
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
	auto id = GetID();
	auto bb = GetBounds();
	return  HandleEvents(bb, id);
}

bool UIElement::HandleEvents(const ImRect& bounds, ImGuiID id)
{

	if (!m_Interactive) return false;

	bool handled = false;

	HandleHoveringEvent(bounds, id, handled);

	HandleClickEvent(bounds , id, handled);

	return handled;
}

void UIElement::HandleHoveringEvent(const ImRect& bounds, ImGuiID id, bool& handled)
{
	bool hoverable = ImGui::ItemHoverable(bounds, id);

	m_Hovered = ImGui::IsItemHovered() && hoverable && IsHoverable();

	if (m_Hovered)
	{
		handled |= true;

		ImGui::SetHoveredID(id);

		ImGui::SetMouseCursor(m_Style.hoveredStyle.cursor);

	}

	if (m_Hovered != m_PreviouslyHovered)
	{
		if (m_Hovered)
		{
			OnHoveredEvent.Broadcast();
		}
		else
		{
			OnUnHoveredEvent.Broadcast();
		}

		m_PreviouslyHovered = m_Hovered;
	}
}

void UIElement::HandleClickEvent(const ImRect& bounds, ImGuiID id, bool& handled)
{
	if (ImGui::IsItemClicked() && ImGui::GetHoveredID() == id)
	{

		handled |= true;

		ImGui::SetActiveID(id, ImGui::GetCurrentWindow());

		OnClickedEvent.Broadcast();

	}
}

void UIElement::DrawToolTip()
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();

	ImVec2 position = ed::CanvasToScreen(GetPosition());
	position += ImGui::GetIO().MousePos;

	auto tooltipStyle = m_Style.m_ToolTipStyle;
	auto fontStyle = tooltipStyle.m_FontStyle;

	ImDrawList* drawlist = ImGui::GetForegroundDrawList(window);
	drawlist->AddText(fontStyle.font, fontStyle.size.value, position, ImColor(fontStyle.color), m_ToolTip.c_str());
}