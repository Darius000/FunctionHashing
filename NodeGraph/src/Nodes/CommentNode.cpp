#include "PCH.h"
#include "CommentNode.h"
#include "NodeGraph/NodeGraph.h"

Comment::Comment()
{
	m_Comment = "This is a comment node!";
	m_TitleStyle = ETitleStyle_::Custom;
	m_Color = {.1f, .1f, .1f , .2f};
}

void Comment::CustomDraw()
{
	
	ImNodes::BeginNodeTitleBar();
	ImGui::SetNextItemWidth(m_DefaultSize.x);
	ImGui::PushStyleColor(ImGuiCol_FrameBg, {0 , 0, 0, 0});
	ImGui::InputText("##comment", &m_Comment);
	ImGui::PopStyleColor();
	ImNodes::EndNodeTitleBar();
	DrawResizeButton();
}

void Comment::DrawResizeButton()
{
	ImVec2 pos = ImNodes::GetNodeScreenSpacePos(GetID());
	ImVec2 dim = ImNodes::GetNodeDimensions(GetID());

	ImDrawList* drawlist = ImGui::GetWindowDrawList();
	ImVec2 size = { 30, 30 };
	ImRect rect = { pos + dim - size, pos + dim };
	drawlist->AddRectFilled(rect.Min, rect.Max, ImGui::GetColorU32({ .1f, .1f , .1f , .1f }));

	ImGuiID id = GetID() + ImHashStr("resizebox");
	ImGui::ItemSize(rect);
	ImGui::ItemAdd(rect, id);

	bool hovered = ImGui::ItemHoverable(rect, id);
	hovered = ImGui::IsMouseHoveringRect(rect.Min, rect.Max, false);

	if (hovered)
	{
		auto window = ImGui::GetCurrentWindow();
		ImGui::SetHoveredID(id);
		ImGui::SetActiveID(id, window);
		ImGui::SetFocusID(id, window);

		ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeNWSE);

		if (ImGui::IsMouseDown(ImGuiMouseButton_Left))
		{
			auto deltaPos = ImGui::GetMouseDragDelta(ImGuiMouseButton_Left, 0.01f);
			m_DefaultSize += deltaPos;
			ImGui::ResetMouseDragDelta(ImGuiMouseButton_Left);			
		}
	}
}

DEFINE_REGISTER_NODE(Comment)