#include "NodeGraph.h"
#include "Events/MouseEvent.h"
#include "imgui-node-editor/imgui_node_editor.h"
#include "imgui-node-editor/imgui_node_editor_internal.h"
#include "imgui.h"
#include "imgui_internal.h"
#include "Debug/Instrumentor.h"
#include "Utilities/VectorUtilities.h"
#include "UIElements/NodeElement.h"
#include <Engine.h>
#include <rttr/type.h>
#include "Runtime/UI/Elements/VerticalBox.h"
#include "UIElements/PinElement.h"
#include "UIElements/EdgeElement.h"
#include "Runtime/BaseObject/BaseObject.h"
#include "Runtime/BaseObject/Selection.h"

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

	CORE_ASSERT(new_node != nullptr);


	auto nodeElement = MakeScope<class NodeElement>(Ref<BaseNode>(new_node));
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
							LOG_ERROR("Error unable to link : reason : {0}", error_message.c_str());
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
		//delete edges
		{
			ed::LinkId deletedlinkid;
			while (ed::QueryDeletedLink(&deletedlinkid))
			{

				if (ed::AcceptDeletedItem())
				{
					for (auto& edge : m_Edges)
					{
						if ((uint64_t)edge->GetID() == (uint64_t)deletedlinkid)
						{
							edge->Destroy();
						}
					}
				}
			}
		}

		//delete nodes
		{
			ed::NodeId deletednodeid;
			while (ed::QueryDeletedNode(&deletednodeid))
			{
				if (ed::AcceptDeletedItem())
				{
					for (auto& node : m_Nodes)
					{
						if ((uint64_t)node->GetID() == (uint64_t)deletednodeid)
						{
							node->Destroy();
						}
					}
				}
			}
		}
	}
	ed::EndDelete();

	
	/*{
		ed::NodeId selectednode;
		ed::GetSelectedNodes(&selectednode, 1);

		auto id = (uint64_t)selectednode.Get();
		auto node = FindNodeByID(id);
		if (node)
		{
			OnObjectSelected.Invoke(node);
		}
	}*/

	ed::End();
	ed::PopStyleVar(3);

	//deselect on graph clicked
	if (ed::IsBackgroundClicked())
	{
		Selection::Select(nullptr);
	}
}

BaseObject* NodeGraph::FindNodeByID(uint64_t id) const
{
	for (auto& node_element : m_Nodes)
	{
		if ((uint64_t)node_element->GetID() == id)
		{
			return node_element.get();
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
			auto id = (uint64_t)input->GetID();
			if (auto pin = Cast<PinElement>(input); pin && id == pinid)
			{
				return pin;
			}
		}

		for (auto& output: node_element->GetOutputs()->GetChildren())
		{
			auto id = (uint64_t)output->GetID();
			if (auto pin = Cast<PinElement>(output); pin && id == pinid)
			{
				return pin;
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
	for (auto it = m_Nodes.begin(); it != m_Nodes.end();)
	{
		auto& nodeElement = (*it);

		if (nodeElement->IsPendingDestroy())
		{
			it = m_Nodes.erase(it);
		}
		else
		{
			nodeElement->DrawElement();
			it++;
		}
	}

	for (auto it = m_Edges.begin(); it != m_Edges.end();)
	{
		auto& edgeElement = (*it);

		if (edgeElement->IsPendingDestroy())
		{
			it = m_Edges.erase(it);
		}
		else
		{
			edgeElement->DrawElement();
			it++;
		}
	}
}
