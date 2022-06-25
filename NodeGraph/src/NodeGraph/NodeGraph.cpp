#include "NodeGraph.h"
#include "Nodes/VariableNodeInterface/VariableNodeInterface.h"
#include "Core/Events/MouseEvent.h"
#include "imgui-node-editor/imgui_node_editor.h"
#include "imgui-node-editor/imgui_node_editor_internal.h"
#include "imgui.h"
#include "imgui_internal.h"
#include "Core\Debug\Instrumentor.h"
#include "Core/Helpers/Vectors/VectorHelper.h"
#include "UIElements/NodeElement.h"
#include <Engine.h>
#include <rttr/type.h>
#include "imgui_stdlib.h"
#include "UIElements/PinElement.h"
#include "UIElements/EdgeElement.h"

namespace ed = ax::NodeEditor;

NodeGraph::NodeGraph()
{
	m_OpenNodePopup = false;
	
}

void NodeGraph::Instantiate(std::string_view name)
{
	auto nodetype = rttr::type::get_by_name(name.data());

	if (!nodetype.is_valid()) return;

	auto new_variant = nodetype.create();
	auto new_node = new_variant.get_value<BaseNode*>();

	assert(new_node != nullptr);


	auto nodeElement = MakeScope<class NodeElement>(new_node);
	ed::CenterNodeOnScreen((uint64_t)nodeElement->GetID());
	m_Nodes.push_back(std::move(nodeElement));	
}

void NodeGraph::Draw()
{
	ed::PushStyleVar(ed::StyleVar_PinRadius, 20.0f);
	ed::PushStyleVar(ed::StyleVar_PinBorderWidth, 2.0f);
	ed::PushStyleVar(ed::StyleVar_LinkStrength, 100.0f);

	ed::Begin("Nodes");

	DrawElements();

	//handle new links
	if (ed::BeginCreate())
	{
		//does editor want to create new link?
		ed::PinId start, end;
		if (ed::QueryNewLink(&start, &end))
		{
			if (start && end)//if its valid accept link
			{
				auto start_pin = FindPin((uint64_t)start);
				auto end_pin = FindPin((uint64_t)end);

				std::string error_message = "";

				if (ed::AcceptNewItem())
				{
					if (CanConnectPins(start_pin, end_pin, error_message))
					{

						auto edge = MakeRef<Edge>((uint64_t)start_pin->GetID(), (uint64_t)end_pin->GetID());
						m_Edges.push_back(MakeScope<EdgeElement>(edge));
					}
					else
					{
						if (!error_message.empty())
						{
							LOG("Error unable to link : reason : %s", error_message.c_str());
						}
					}
				}
			}
		}

		ed::PinId pinId = 0;
		if (ed::QueryNewNode(&pinId))
		{
			if (ed::AcceptNewItem())
			{
				
			}
		}
	}
	ed::EndCreate();

	//handle deleted links
	if(ed::BeginDelete())
	{
		ed::LinkId deletedlinkid;
		while (ed::QueryDeletedLink(&deletedlinkid))
		{
			
			if (ed::AcceptDeletedItem())
			{
				for (int i = 0; i < m_Edges.size(); i++)
				{
					auto& link = m_Edges[i];
					auto edge_ids = link->GetEdge()->GetIds();

					if ((uint64_t)edge_ids.first == (uint64_t)deletedlinkid || (uint64_t)edge_ids.second == (uint64_t)deletedlinkid)
					{
						Helpers::Vector::Remove(m_Edges, link);
					}
				}
			}
		}

		ed::NodeId deletednodeid;
		while (ed::QueryDeletedNode(&deletednodeid))
		{
			if (ed::AcceptDeletedItem())
			{
				ImGuiID id = (ImGuiID)deletednodeid.Get();
				/*if (m_Nodes.find(id) != m_Nodes.end())
				{
					m_Nodes[id]->Destroy();
					break;
				}*/
			}
		}
	}
	ed::EndDelete();

	
	{
		ed::NodeId selectednode;
		ed::GetSelectedNodes(&selectednode, 1);

		auto id = (uint64_t)selectednode.Get();
		auto node = FindNodeByID(id);
		m_SelectedObject = node;
	}

	ed::End();
	ed::PopStyleVar(3);
}

NodeEditorObject* NodeGraph::GetSelectedObject()
{
	return m_SelectedObject; 
}

NodeEditorObject* NodeGraph::FindNodeByID(uint64_t id) const
{
	for (auto& node_element : m_Nodes)
	{
		if ((uint64_t)node_element->GetID() == id)
		{
			return node_element->GetNode();
		}
	}

	return nullptr;
}

PinElement* NodeGraph::FindPin(uint64_t pinid) const
{
	for (auto& node_element : m_Nodes)
	{
		for (auto& input : node_element->GetInputs()->GetChildren())
		{
			if (auto pin = Cast<PinElement>(input); pin && (uint64_t)pin->GetID() == pinid)
			{
				return pin.get();
			}
		}

		for (auto& output: node_element->GetOutputs()->GetChildren())
		{
			if (auto pin = Cast<PinElement>(output); pin && (uint64_t)output->GetID() == pinid)
			{
				return pin.get();
			}
		}
	}

	return nullptr;
}



bool NodeGraph::CanConnectPins(PinElement* start, PinElement* end, std::string& error)
{
	if (start && end)
	{
		auto start_type = start->GetType();
		auto end_type = end->GetType();

		bool different_kinds = start->GetKind() != end->GetKind();
		bool same_type = start_type == end_type;
		bool can_connect = different_kinds && same_type;

		if (!different_kinds) error = "Pin kinds are not different!";
		if (!same_type) error = "Pin types do not match!";

		return  can_connect;
	}

	error = "Not valid pins!";

	return false;
}


void NodeGraph::DrawNodeListContextMenu()
{

	if (ImGui::BeginPopupContextItem("Nodes"))
	{
		const ImVec2 click_pos = ImGui::GetMousePosOnOpeningCurrentPopup();

		ImGui::EndPopup();
	}
}

void NodeGraph::DrawElements()
{
	for (size_t i = 0; i < m_Nodes.size(); i++)
	{
		auto& nodeElement = m_Nodes[i];

		nodeElement->DrawElement();
	}

	for (size_t j = 0; j < m_Edges.size(); j++)
	{
		auto& edge_element = m_Edges[j];
		edge_element->DrawElement();
	}
}
