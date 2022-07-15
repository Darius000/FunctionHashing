#pragma once

#include "UIElement.h"
#include "LayoutSlot.h"
#include "Templates/TSubClass.h"
#include "LayoutConfig.h"

class LayoutElement : public UIElement
{
	using Slots = std::vector<Ref<LayoutSlot>>;

protected:
	LayoutElement() {};

protected:

	virtual void BeginLayout(uint64_t id) {};

	virtual void EndLayout() {};

	virtual TSubClass<LayoutSlot> GetSlotClass() { return TSubClass<LayoutSlot>(); };

public:
	LayoutSlot* AddChild(UIElement* element);

	LayoutSlot* AddChild(UIElement* element, const LayoutConfig& config);

	bool RemoveChild(UIElement* element);

	bool RemoveChildAt(uint64_t index);

	std::vector<UIElement*> GetChildren();

	const Slots& GetSlots() { return m_Slots; }

	size_t GetNumChildren() const { return m_Slots.size(); }

	void ClearChildren();

	ImVec2 m_ItemSpacing = { 10.0f, 10.0f };


protected:

	virtual void OnAddSlot(class LayoutSlot* slot) {};

	virtual void OnRemoveSlot(class LayoutSlot* slot) {};

	void OnDrawElement() override;

private:
	Slots m_Slots;
};


