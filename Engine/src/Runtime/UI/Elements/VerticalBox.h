#pragma once

#include "Layouts.h"
#include "VerticalBoxSlot.h"

class VerticalBox : public LayoutElement
{
public:

	VerticalBox();

protected:

	void BeginLayout(uint64_t id) override;

	void EndLayout() override;

	virtual TSubClass<LayoutSlot> GetSlotClass() override { return TSubClass<VerticalBoxSlot>(); };
};