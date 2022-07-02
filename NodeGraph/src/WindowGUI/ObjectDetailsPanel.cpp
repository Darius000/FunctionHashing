#include "ObjectDetailsPanel.h"
#include "Runtime/BaseObject/BaseObject.h"
#include "Runtime/UI/Inspectors/InspectorRegistry.h"
#include "Runtime/BaseObject/Selection.h"

ObjectDetailsPanel::ObjectDetailsPanel(ImGuiWindowFlags flags ,ImGuiID id)
	:ImGuiPanel("Details", flags, id)
{
}

void ObjectDetailsPanel::OnRenderMenuBar()
{
}

void ObjectDetailsPanel::OnRenderWindow()
{
	DrawSelectedObj();
}

void ObjectDetailsPanel::DrawSelectedObj()
{
	auto selection = Selection::Get();
	if (selection)
	{
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(5, 5));
		ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(.1f, .1f, .1f, 1.0f));

		auto item_width = ImGui::GetContentRegionAvail().x - 20.0f;
		ImGui::SetCursorPosX(10.0f);

		//ImGui::BeginVertical("details");

		rttr::variant var = selection.get();
		InspectorRegistry::InspectVar(var);

		//ImGui::EndVertical();

		ImGui::PopStyleVar();
		ImGui::PopStyleColor();
	}
}
