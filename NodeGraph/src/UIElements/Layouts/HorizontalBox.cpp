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
}