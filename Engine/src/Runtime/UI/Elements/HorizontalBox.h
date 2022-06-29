#pragma once

#include "Layouts.h"
#include "HorizontalBoxSlot.h"

class HorizontalBox : public LayoutElement
{
public:

	HorizontalBox();

protected:
	void BeginLayout(uint64_t id) override;

	void EndLayout() override;

	virtual TSubClass<LayoutSlot> GetSlotClass() override { return TSubClass<HorizontalBoxSlot>(); };
};