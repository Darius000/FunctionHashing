#include "PCH.h"
#include "VerticalBox.h"


VerticalBox::VerticalBox()
{
}

void VerticalBox::BeginLayout(uint64_t id)
{
	ImGui::BeginVertical((uint32_t)id);
}

void VerticalBox::EndLayout()
{
	ImGui::EndVertical();

	/*ImGui::GetWindowDrawList()->AddRect(
		ImGui::GetItemRectMin(), ImGui::GetItemRectMax(), IM_COL32(255, 180, 0, 255));*/
}
