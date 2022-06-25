#include "PCH.h"
#include "NodeElement.h"
#include "imgui-node-editor/imgui_node_editor.h"
#include "Nodes/BaseNode.h"
#include "LabelElement.h"
#include "InputPin.h"

namespace ed = ax::NodeEditor;

NodeElement::NodeElement(class BaseNode* node)
{
	m_Name = node->GetName();
	m_Node = node;

	UI::MenuItem copy{ "Copy", []() {} };

	UI::MenuItem deleteItem{ "Delete", []() {} };

	m_Menu = MakeRef<UI::GenericMenu>("NodeContextMenu");
	m_Menu->AddMenuItem(copy);
	m_Menu->AddMenuItem(deleteItem);

	m_InputContainer = new VerticalElement();
	m_OutputContainer = new VerticalElement();

	auto node_element = new VerticalElement();
	auto header = new HorizontalElement();
	auto content = new HorizontalElement();

	header->AddChild(new LabelElement("Header", GetName()));

	content->AddChild(m_InputContainer);
	content->AddChild(m_OutputContainer);

	node_element->AddChild(header);
	node_element->AddChild(content);

	AddChild(node_element);

	for (auto property : rttr::type::get(*node).get_properties())
	{
		auto meta_data = property.get_metadata("Kind");
		if (meta_data)
		{
			auto kind = meta_data.get_value<std::string>() == "Input" ? ed::PinKind::Input : ed::PinKind::Output;

			AddPinElement(property.get_name().data(), kind, property, rttr::instance(m_Node), false);
		}

	}
}

void NodeElement::BeginLayout(uint32_t id)
{
	ed::PushStyleColor(ed::StyleColor_NodeBg, m_Node->GetColor());
	ed::BeginNode(id);
}

void NodeElement::EndLayout()
{
	ed::EndNode();
	ed::PopStyleColor();

	auto pos = ed::GetNodePosition((uint32_t)GetID());
	SetPosition(pos);
}

void NodeElement::SetPosition(const ImVec2& pos)
{
	m_Node->m_Position = { pos.x, pos.y };
}

void NodeElement::AddPinElement(std::string_view name, ed::PinKind kind, rttr::property& property, rttr::instance& obj, bool canMultiConnect)
{
	if (kind == ed::PinKind::Input)
	{
		auto pin = new InputPin(name, property, obj, canMultiConnect);
		m_InputContainer->AddChild(pin);
	}
	else
	{
		auto pin = new OutputPin(name, property, obj, canMultiConnect);
		m_OutputContainer->AddChild(pin);
	}
}

bool NodeElement::HandleEvents()
{
	bool handled = LayoutElement::HandleEvents();

	if (!handled)
	{
		if (ImGui::IsItemHovered())
		{
			auto meta_data = rttr::type::get(*m_Node).get_metadata(ClassMetaData::Description);

			if (meta_data)
			{
				auto tooltip = meta_data.get_value<std::string>();
				ImGui::SetCursorPos(ImGui::GetMousePos());
				ImGui::BeginTooltip();
				ImGui::TextUnformatted(tooltip.c_str());
				ImGui::EndTooltip();
			}
					
		}

		static ed::NodeId contextID = 0;
		ed::Suspend();
		if (ed::ShowNodeContextMenu(&contextID))
		{
			m_Menu->OpenMenu();

		}
		ed::Resume();


		ed::Suspend();

		//context menu
		handled = m_Menu->ShowAsContext();

		ed::Resume();
	}

	return handled;
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
