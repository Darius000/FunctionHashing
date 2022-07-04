#include "NodeElement.h"
#include "Runtime/UI/Elements/VerticalBox.h"
#include "Runtime/UI/Elements/HorizontalBox.h"
#include "Runtime/UI/Elements/LabelElement.h"
#include "imgui-node-editor/imgui_node_editor.h"
#include "Nodes/BaseNode.h"
#include "InputPin.h"
#include "Runtime/BaseObject/Selection.h"

namespace ed = ax::NodeEditor;

NodeElement::NodeElement(const Ref<class BaseNode>& node)
{
	m_Name = node->GetName();
	m_Node = node;

	OnDestroyed.AddBinding([&](BaseObject* objPtr) {
		m_Node->Destroy();
	});

	MenuItem copy{ "Copy", []() {} };

	MenuItem deleteItem{ "Delete", [&]() {
		ed::DeleteNode((uint64_t)GetID());
	} };

	m_Menu = MakeRef<Menu>("NodeContextMenu");
	m_Menu->AddMenuItem(copy);
	m_Menu->AddMenuItem(deleteItem);
	m_Menu->m_CanOpenMenuCallBack += []()
	{
		static ed::NodeId contextID = 0;
		ed::Suspend();
		bool opened = ed::ShowNodeContextMenu(&contextID);
		ed::Resume();
		return opened;
	};

	m_InputContainer = new VerticalBox();
	m_OutputContainer = new VerticalBox();

	auto node_element = new VerticalBox();
	auto header = new HorizontalBox();
	auto content = new HorizontalBox();
	auto node_label = new LabelElement("Header", GetName());

	auto binding = [&]()
	{
		return m_Node->GetName();
	};

	node_label->m_Binding += binding;

	auto header_slot = Cast<HorizontalBoxSlot>(header->AddChild(node_label));
	header_slot->m_StartWeight = 0.0f;
	//header_slot->m_EndSpacing = 1.0f;

	Cast<HorizontalBoxSlot>(content->AddChild(m_InputContainer))->m_StartWeight = 1.0f;
	Cast<HorizontalBoxSlot>(content->AddChild(m_OutputContainer))->m_StartWeight = 1.0f;

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

void NodeElement::BeginLayout(uint64_t id)
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

	if (ImGui::IsItemClicked())
	{
		ed::SelectNode((uint32_t)GetID(), true);

		Selection::Select(m_Node);
	}

	if (ImGui::IsItemHovered())
	{
		auto meta_data = rttr::type::get(*m_Node).get_metadata(ClassMetaData::Description);

		if (meta_data)
		{
			ICONINFO ii;
			BITMAP bitmap;
			GetIconInfo(GetCursor(), &ii);
			GetObject(ii.hbmColor, sizeof(BITMAP), &bitmap);
			float size = (float)bitmap.bmWidth / 2.0f;

			auto tooltip = meta_data.get_value<std::string>();
			ImGui::SetNextWindowPos(ed::CanvasToScreen(GetPosition()) + ImGui::GetMousePos() + ImVec2(size, 0.0f) );
			ImGui::BeginTooltip();
			ImGui::TextUnformatted(tooltip.c_str());
			ImGui::EndTooltip();
		}

	}

	ed::Suspend();

	//context menu
	m_Menu->Show();

	ed::Resume();
}

void NodeElement::SetPosition(const ImVec2& pos)
{
	m_Node->m_Position = { pos.x, pos.y };
}

void NodeElement::AddPinElement(std::string_view name, ed::PinKind kind, const rttr::property& property, const rttr::instance& obj, bool canMultiConnect)
{
	if (kind == ed::PinKind::Input)
	{
		auto pin = new InputPin(name, property, obj, canMultiConnect);
		auto input_slot = Cast<VerticalBoxSlot>(m_InputContainer->AddChild(pin));
	}
	else
	{
		auto pin = new OutputPin(name, property, obj, canMultiConnect);
		auto output_slot = Cast<VerticalBoxSlot>(m_OutputContainer->AddChild(pin));
	}
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
