#pragma once

#include "UIElement.h"
#include "Layouts.h"

class LayoutSlot : public UIElement
{
public:

	LayoutSlot() {}

	virtual ~LayoutSlot(){}

	void OnDrawElement() override;

protected:
	virtual void OnBeginSlotLayout() {}

	virtual void OnEndSlotLayout() {}

public:
	Ref<UIElement> m_Content;

	Ref<LayoutElement> m_Parent;

	REFLECTABLEV(UIElement)
};
