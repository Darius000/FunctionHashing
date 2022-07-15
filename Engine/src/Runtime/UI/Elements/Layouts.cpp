#include "PCH.h"
#include "Layouts.h"
#include "LayoutSlot.h"
#include "Utilities/VectorUtilities.h"
#include "HorizontalBoxSlot.h"

LayoutSlot* LayoutElement::AddChild(UIElement* element)
{
	LayoutSlot* new_slot = GetSlotClass().Instaniate();

	if (new_slot)
	{
		auto slot_ref = Ref<LayoutSlot>(new_slot);

		slot_ref->m_Content = Ref<UIElement>(element);
		slot_ref->m_Parent = Ref<LayoutElement>(this);

		element->m_ParentSlot = slot_ref;

		m_Slots.push_back(slot_ref);

		OnAddSlot(new_slot);
	}

	return new_slot;
}

LayoutSlot* LayoutElement::AddChild(UIElement* element, const LayoutConfig& config)
{
	LayoutSlot* new_slot = GetSlotClass().Instaniate({config});

	if (new_slot)
	{
		auto slot_ref = Ref<LayoutSlot>(new_slot);

		slot_ref->m_Content = Ref<UIElement>(element);
		slot_ref->m_Parent = Ref<LayoutElement>(this);

		element->m_ParentSlot = slot_ref;

		m_Slots.push_back(slot_ref);

		OnAddSlot(new_slot);
	}

	return new_slot;
}

bool LayoutElement::RemoveChild(UIElement* element)
{
	auto index = VectorUtilities::FindIndex(m_Slots, [&](const Ref<LayoutSlot>& slot)
		{
			return slot->m_Content.get() == element;
		});

	return RemoveChildAt(index);
}


bool LayoutElement::RemoveChildAt(uint64_t index)
{
	if (index < 0 || index >= m_Slots.size()) return false;

	LayoutSlot* slot = m_Slots[index].get();

	OnRemoveSlot(slot);

	return VectorUtilities::RemoveAt(m_Slots, index);
}

std::vector<UIElement*> LayoutElement::GetChildren()
{
	std::vector<UIElement*> results;

	for (auto slot : GetSlots())
	{
		results.push_back(slot->m_Content.get());
	}

	return results;
}

void LayoutElement::ClearChildren()
{
	m_Slots.clear();
}

void LayoutElement::OnDrawElement()
{
	uint64_t id = (uint64_t)GetID();

	ImGui::PushStyleVar(ImGuiStyleVar_::ImGuiStyleVar_ItemInnerSpacing, m_ItemSpacing);

	BeginLayout(id);

	for (auto child : GetSlots())
	{
		child->DrawElement();
	}


	EndLayout();

	ImGui::PopStyleVar();

	//Debug
	/*ImGui::GetWindowDrawList()->AddRect(
		ImGui::GetItemRectMin(), ImGui::GetItemRectMax(), IM_COL32(180, 255, 0, 255));*/

}




