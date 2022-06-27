#include "PCH.h"
#include "HorizontalBoxSlot.h"

void HorizontalBoxSlot::OnBeginSlotLayout()
{
	ImGui::Spring(m_StartWeight, m_StartSpacing);
}

void HorizontalBoxSlot::OnEndSlotLayout()
{
	ImGui::Spring(m_EndWeight, m_EndSpacing);
}
