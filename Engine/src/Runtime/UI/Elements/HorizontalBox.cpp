#include "PCH.h"
#include "HorizontalBox.h"


HorizontalBox::HorizontalBox()
{
}

void HorizontalBox::BeginLayout(uint64_t id)
{
	ImGui::BeginHorizontal((uint32_t)id);

}

void HorizontalBox::EndLayout()
{
	ImGui::EndHorizontal();

	/*ImGui::GetWindowDrawList()->AddRect(
		ImGui::GetItemRectMin(), ImGui::GetItemRectMax(), IM_COL32(255, 0, 0, 255));*/
}