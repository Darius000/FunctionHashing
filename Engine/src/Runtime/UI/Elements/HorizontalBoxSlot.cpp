#include "PCH.h"
#include "HorizontalBoxSlot.h"

void HorizontalBoxSlot::OnBeginSlotLayout()
{
	ImGui::Spring(m_Configuration.m_StartWeight, m_Configuration.m_StartSpacing);

	/*ImGui::GetWindowDrawList()->AddRect(
		ImGui::GetItemRectMin(), ImGui::GetItemRectMax(), IM_COL32(255, 255, 0, 255));*/
}

void HorizontalBoxSlot::OnEndSlotLayout()
{
	ImGui::Spring(m_Configuration.m_EndWeight, m_Configuration.m_EndSpacing);

	/*ImGui::GetWindowDrawList()->AddRect(
		ImGui::GetItemRectMin(), ImGui::GetItemRectMax(), IM_COL32(255, 255, 180, 255));*/
}