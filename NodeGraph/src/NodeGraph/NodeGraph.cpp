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


	auto nodeElement = MakeRef<class NodeElement>(Ref<BaseNode>(new_node));
	nodeElement->m_SetRootEvent += [&](const Ref<BaseNode>& node) { m_Root = node; };
	nodeElement->OnDestroyedEvent += [&](BaseObject* obj) {
		if (NodeElement* element = Cast<NodeElement>(obj))
		{
			if (element->GetNode() == m_Root) m_Root = nullptr;
		}
	};

	ed::CenterNodeOnScreen((uint64_t)nodeElement->GetID());
	m_Elements.push_back(nodeElement);	
}

void NodeGraph::Update(float deltatime)
{
	if(m_Running)
	{
		if (!m_Paused)
		{
			LOG_TRACE("Running");

			if (m_Root)
			{
				m_Root->Execute();
			}
		}
		else
		{
			LOG_WARN("Paused");
		}	
	}
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
						m_Elements.push_back(MakeScope<EdgeElement>(edge));
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
					for (auto& element : m_Elements)
					{
						if ((uint64_t)element->GetID() == (uint64_t)deletedlinkid)
						{
							element->Destroy();
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
					for (auto& element : m_Elements)
					{
						if ((uint64_t)element->GetID() == (uint64_t)deletednodeid)
						{
							element->Destroy();
						}
					}
				}
			}
		}
	}
	ed::EndDelete();



	ed::Suspend();
	if (ed::ShowBackgroundContextMenu())
	{
		ImGui::OpenPopup("Nodes");
	}

	DrawNodeListContextMenu();

	ed::Resume();

	ed::End();
	ed::PopStyleVar(3);

	
	//deselect on graph clicked
	if (ed::IsBackgroundClicked())
	{
		Selection::Select(nullptr);

	}
}

void NodeGraph::Run()
{
	m_Running = true;
}

void NodeGraph::Stop()
{
	m_Running = false;
}

void NodeGraph::Pause()
{
	m_Paused = true;
}

void NodeGraph::Resume()
{
	m_Paused = false;
}

BaseObject* NodeGraph::FindNodeByID(uint64_t id) const
{
	for (auto& element : m_Elements)
	{
		if ((uint64_t)element->GetID() == id)
		{
			return element.get();
		}
	}

	return nullptr;
}

PinElement* NodeGraph::FindPin(uint64_t pinid) const
{
	for (auto element : m_Elements)
	{
		auto node = Cast<NodeElement>(element);
		for ( auto& input: node->GetInputs()->GetChildren())
		{
			auto id = (uint64_t)input->GetID();
			if (auto pin = Cast<PinElement>(input); pin && id == pinid)
			{
				return pin;
			}
		}

		for (auto& output: node->GetOutputs()->GetChildren())
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
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 5.0f, 5.0f });
	ImGui::PushStyleColor(ImGuiCol_PopupBg, ImVec4(.2f, .2f, .2f, 1.0f));
	if (ImGui::BeginPopupContextItem("Nodes"))
	{
		const ImVec2 click_pos = ImGui::GetMousePosOnOpeningCurrentPopup();

		auto nodeType = rttr::type::get_by_name("Node");

		for (auto derived_type : nodeType.get_derived_classes())
		{
			auto name = derived_type.get_name();
			if (ImGui::MenuItem(name.data()))
			{
				Instantiate(name);
			}
		}

		ImGui::EndPopup();
	}
	ImGui::PopStyleColor();
	ImGui::PopStyleVar();
}

void NodeGraph::DrawElements()
{
	for (auto it = m_Elements.begin(); it != m_Elements.end();)
	{
		auto& element = (*it);

		if (element->IsPendingDestroy())
		{
			it = m_Elements.erase(it);
		}
		else
		{
			element->DrawElement();
			it++;
		}
	}
}
