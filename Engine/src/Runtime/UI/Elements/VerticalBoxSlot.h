#pragma once

#include "HorizontalBoxSlot.h"

class VerticalBoxSlot : public LayoutSlot
{
public:
	VerticalBoxSlot();
	VerticalBoxSlot(const LayoutConfig& config) ;

	virtual void OnBeginSlotLayout() override;

	virtual void OnEndSlotLayout() override;

	SlotConfiguration m_Configuration;

	REFLECTABLEV(LayoutSlot)
};