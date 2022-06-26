#ifndef LAYOUTSLOT_H
#define LAYOUTSLOT_H

#include "UIElements/UIElement.h"
#include "UIElements/Layouts/Layouts.h"

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

	REFLECTABLEV()
};

#endif