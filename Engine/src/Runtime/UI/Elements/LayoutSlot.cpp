#include "PCH.h"
#include "LayoutSlot.h"

void LayoutSlot::OnDrawElement()
{
	OnBeginSlotLayout();

	m_Content->DrawElement();

	OnEndSlotLayout();
}
