#include "Layouts.h"
#include "UIElements/Slots/LayoutSlot.h"
#include "Core/Helpers/Vectors/VectorHelper.h"

LayoutSlot* LayoutElement::AddChild(UIElement* element)
{
	LayoutSlot* new_slot = GetSlotClass().Instaniate();

	auto slot_ref = Ref<LayoutSlot>(new_slot);

	slot_ref->m_Content = Ref<UIElement>(element);
	slot_ref->m_Parent = Ref<LayoutElement>(this);

	element->m_ParentSlot = slot_ref;

	m_Slots.push_back(slot_ref);

	OnAddSlot(new_slot);

	return new_slot;
}

bool LayoutElement::RemoveChild(UIElement* element)
{
	auto index = Helpers::Vector::FindIndex(m_Slots, [&](const Ref<LayoutSlot>& slot)
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

	return Helpers::Vector::RemoveAt(m_Slots, index);
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

bool LayoutElement::HandleEvents()
{
	bool handled = false;
	for (auto child : GetSlots())
	{
		handled |= child->m_Content->HandleEvents();
		if (handled)
		{
			break;
		}
	}

	return handled;
}

void LayoutElement::ClearChildren()
{
	m_Slots.clear();
}

void LayoutElement::OnDrawElement()
{
	uint64_t id = (uint64_t)GetID();

	BeginLayout(id);

	for (auto child : GetSlots())
	{
		child->DrawElement();
	}


	EndLayout();

	//Debug
	/*ImGui::GetWindowDrawList()->AddRect(
		ImGui::GetItemRectMin(), ImGui::GetItemRectMax(), IM_COL32(180, 255, 0, 255));*/

}




