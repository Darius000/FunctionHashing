#include "PCH.h"
#include "VerticalBoxSlot.h"

VerticalBoxSlot::VerticalBoxSlot()
{
}

VerticalBoxSlot::VerticalBoxSlot(const LayoutConfig& config)
	: m_Configuration((const SlotConfiguration&)config)
{

}

void VerticalBoxSlot::OnBeginSlotLayout()
{
	ImGui::Spring(m_Configuration.m_StartWeight, m_Configuration.m_StartSpacing);

	/*ImGui::GetWindowDrawList()->AddRect(
		ImGui::GetItemRectMin(), ImGui::GetItemRectMax(), IM_COL32(0, 255, 255, 255));*/
}

void VerticalBoxSlot::OnEndSlotLayout()
{
	ImGui::Spring(m_Configuration.m_EndWeight, m_Configuration.m_EndSpacing);

	/*ImGui::GetWindowDrawList()->AddRect(
		ImGui::GetItemRectMin(), ImGui::GetItemRectMax(), IM_COL32(0, 255, 255, 255));*/
}
