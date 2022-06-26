#ifndef HORIZONTALBOX_SLOT
#define HORIZONTALBOX_SLOT

#include "LayoutSlot.h"

class HorizontalBoxSlot : public LayoutSlot
{
protected:
	virtual void OnBeginSlotLayout() override;

	virtual void OnEndSlotLayout() override;

public:
	float m_StartWeight = 1.0f;

	float m_StartSpacing = -1.0f;

	float m_EndWeight = 1.0f;

	float m_EndSpacing = -1.0f;

	REFLECTABLEV(LayoutSlot)
};

#endif
