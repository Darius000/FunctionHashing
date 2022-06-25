#include "Layouts.h"
#include "Core/Helpers/Vectors/VectorHelper.h"

void LayoutElement::AddChild(UIElement* element)
{
	element->SetParent(this);

	m_Children.push_back(Ref<UIElement>(element));
}

void LayoutElement::RemoveElement(UIElement* element)
{
	Helpers::Vector::Remove(m_Children, Ref<UIElement>(element));

	element->SetParent(nullptr);
}

void LayoutElement::RemoveElement(const std::string& name)
{
	auto element = Helpers::Vector::FindPred(m_Children, [&](Ref<UIElement>& element) {
		return element->GetName() == name;
		});

	Helpers::Vector::Remove(m_Children, element);

	element->SetParent(nullptr);
}

bool LayoutElement::HandleEvents()
{
	bool handled = false;
	for (auto child : GetChildren())
	{
		handled |= child->HandleEvents();
		if (handled)
		{
			break;
		}
	}

	return handled;
}

void LayoutElement::Clear()
{
	m_Children.clear();
}

void LayoutElement::OnDrawElement()
{
	uint32_t id = (uint32_t)GetID();

	BeginLayout(id);

	for (auto child : GetChildren())
	{
		OnBeginChildLayout();
		child->DrawElement();
		OnEndChildLayout();
	}


	EndLayout();

	ImGui::GetWindowDrawList()->AddRect(
		ImGui::GetItemRectMin(), ImGui::GetItemRectMax(), IM_COL32(180, 255, 0, 255));

}


HorizontalElement::HorizontalElement()
{
}

void HorizontalElement::BeginLayout(uint32_t id)
{
	ImGui::BeginHorizontal(id);

}

void HorizontalElement::EndLayout()
{
	ImGui::EndHorizontal();
}

void HorizontalElement::OnBeginChildLayout()
{
	ImGui::Spring(1);
}

void HorizontalElement::OnEndChildLayout()
{
	ImGui::Spring(1, 1);
}

void VerticalElement::BeginLayout(uint32_t id)
{
	ImGui::BeginVertical(id);
}

void VerticalElement::EndLayout()
{
	ImGui::EndVertical();
}

void VerticalElement::OnBeginChildLayout()
{
	ImGui::Spring(1);
}

void VerticalElement::OnEndChildLayout()
{
	ImGui::Spring(0);
}
