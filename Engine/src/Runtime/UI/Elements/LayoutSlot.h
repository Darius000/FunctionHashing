#pragma once

#include "UIElement.h"
#include "Layouts.h"
#include "LayoutConfig.h"

class LayoutSlot : public UIElement
{
public:

	LayoutSlot() {};

	LayoutSlot(const LayoutConfig& config) {}

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
