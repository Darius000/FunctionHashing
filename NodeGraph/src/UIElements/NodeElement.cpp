#include "PCH.h"
#include "NodeElement.h"
#include "imgui-node-editor/imgui_node_editor.h"
#include "Nodes/BaseNode.h"
#include "LabelElement.h"

namespace ed = ax::NodeEditor;

NodeElement::NodeElement(class BaseNode* node)
{
	m_Node = node;

	UI::MenuItem copy{ "Copy", []() {} };

	UI::MenuItem deleteItem{ "Delete", []() {} };

	m_Menu = MakeRef<UI::GenericMenu>("NodeContextMenu");
	m_Menu->AddMenuItem(copy);
	m_Menu->AddMenuItem(deleteItem);
}

void NodeElement::DrawElement(ImDrawList* drawlist)
{
	auto id = (ImGuiID)m_Node->GetID();

	ed::PushStyleColor(ed::StyleColor_NodeBg, m_Node->GetColor());
	ed::BeginNode(id);

	ImGui::Dummy({ 200, 50 });

	ed::EndNode();
	ed::PopStyleColor();

	static ed::NodeId contextID = 0;
	ed::Suspend();
	if (ed::ShowNodeContextMenu(&contextID))
	{
		std::cout << "Context \n";
		m_Menu->OpenMenu();
	}
	ed::Resume();

	bool isSelected = ed::IsActive();
	auto pos = ed::GetNodePosition(id);
	auto size = ed::GetNodeSize(id);
	auto nodeDrawList = ed::GetNodeBackgroundDrawList(id);
	auto node_Border_Width = ed::GetStyle().NodeBorderWidth;
	auto node_rounding = ed::GetStyle().NodeRounding ;
	

	ImVec2 headerSize = { size.x - node_Border_Width * 2.0f, 30.0f };
	ImRect headerbb{ pos.x  + node_Border_Width, pos.y + node_Border_Width , pos.x + headerSize.x, pos.y + headerSize.y };


	DrawHeader(headerbb.Min, headerSize, m_Node->GetHeaderColor(), node_rounding, ImDrawCornerFlags_Top, nodeDrawList);

	DrawTitle(m_Node->GetName(), headerbb.Min + ImVec2(node_rounding, 0.0f), {}, nodeDrawList);

	DrawSeperator({ headerbb.Min.x, headerbb.Max.y }, 
		{ headerSize.x, 1.0f }, nodeDrawList);

	
	SetPosition(pos);

	if (ImGui::IsItemHovered())
	{
		DrawToolTip("Tooltip", drawlist);
	}

	ed::Suspend();


	//context menu
	m_Menu->ShowAsContext();

	ed::Resume();
	
}

void NodeElement::SetPosition(const ImVec2& pos)
{
	m_Node->m_Position = { pos.x, pos.y };
}

void NodeElement::DrawToolTip(const std::string& text, ImDrawList* drawlist)
{

	ImVec2 position = { m_Node->m_Position.x, m_Node->m_Position.y };
	position += ImGui::GetIO().MousePos;

	drawlist->AddText(ImGui::GetDefaultFont(), 13.0f, position, ImColor(1.0f, 1.0f, 1.0f, 1.0f), text.c_str());
}

void NodeElement::DrawSeperator(const ImVec2& position, const ImVec2& size, ImDrawList* drawlist)
{
	ImRect bb = { position, position + size };
	drawlist->AddRectFilled(bb.Min, bb.Max + ImVec2(0.0f, size.y * .5f), ImColor(1.0f, 1.0f, 1.0f, 1.0f), 0.0f);
}

void NodeElement::DrawTitle(const std::string& title, const ImVec2& position, const ImVec2& size, ImDrawList* drawlist)
{
	auto textSize = ImGui::CalcTextSize(title.c_str());
	drawlist->AddText(ImGui::GetDefaultFont(), 12.0f, position + ImVec2{0.0f, textSize.y * .5f}, 
		ImColor(1.0f, 1.0f, 1.0f, 1.0f), title.c_str());
}

void NodeElement::DrawHeader(const ImVec2& position, const ImVec2& size, const ImVec4& color, float rounding, ImDrawCornerFlags flags, ImDrawList* drawlist)
{
	ImRect bb = { position, position + size };
	drawlist->AddRectFilled(bb.Min, bb.Max, ImColor(color), rounding, flags);

}
