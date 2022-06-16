#include "NodeGraph.h"
#include "DataTypes/Property.h"
#include "DataTypes/DataTypeRegistry.h"
#include "Nodes/VariableNodeInterface/VariableNodeInterface.h"
#include "Core/Events/MouseEvent.h"
#include "imgui-node-editor/imgui_node_editor.h"
#include "imgui-node-editor/imgui_node_editor_internal.h"
#include "imgui.h"
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
	PROFILE_FUNCTION();
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
	PROFILE_FUNCTION();

	DrawVariableList();

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

//Ref<IProperty> NodeGraph::FindProperty(ImGuiID id)
//{
//	auto it = std::find_if(m_Properties.begin(), m_Properties.end(), [id](Ref<IProperty>& prop)
//	{
//		return prop->GetID() == id;
//	});
//
//	return it != m_Properties.end() ? *it : nullptr;
//}

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
		for (auto& child : node_element->GetChildren())
		{
			if (auto& pin_element = Cast<PinElement>(child))
			{
				if ((uint64_t)pin_element->GetID() == pinid)
				{
					return pin_element.get();
				}
			}
		}
	}

	return nullptr;
}

void NodeGraph::DrawVariableList()
{
	if (ImGui::Begin("Variables"))
	{
		DrawAddNewProperty();
	
		for (auto it = m_Properties.begin(); it != m_Properties.end();)
		{
			if ((*it)->IsPendingDestroy())
			{
				if(m_SelectedObject == it->get()) m_SelectedObject = nullptr;

				//remove property from vector
				it = m_Properties.erase(it);
			}
			else
			{
				//render property in window
				DrawVariableListProp(*it);
				++it;
			}

		}

	}

	ImGui::End();


}


bool NodeGraph::CanConnectPins(PinElement* start, PinElement* end, std::string& error)
{
	if (start && end)
	{
		bool different_kinds = start->GetKind() != end->GetKind();
		bool same_type = start->GetType() == end->GetType();
		bool can_connect = different_kinds && same_type;

		if (!different_kinds) error = "Pin kinds are not different!";
		if (!same_type) error = "Pin types do not match!";

		return  can_connect;
	}

	error = "Not valid pins!";

	return false;
}

void NodeGraph::DrawAddNewProperty()
{
	float width = ImGui::GetContentRegionAvail().x;

	ImGui::BeginGroup();

	if (ImGui::Button("Add New Variable", { width, 20 }))
	{
		ImGui::OpenPopup("DataTypesPopUp");
	}

	if (ImGui::BeginPopup("DataTypesPopUp"))
	{
		for (auto& registeredtype : DataTypeRegistry::RegisteredTypes())
		{
			if (ImGui::Selectable(registeredtype.c_str()))
			{
				auto type = DataTypeRegistry::Instaniate(registeredtype);
				
				m_Properties.emplace_back(type);
			}
		}
		ImGui::EndPopup();
	}

	ImGui::EndGroup();
}

void NodeGraph::DrawNodeListContextMenu()
{

	if (ImGui::BeginPopupContextItem("Nodes"))
	{
		const ImVec2 click_pos = ImGui::GetMousePosOnOpeningCurrentPopup();

		ImGui::EndPopup();
	}
}

void NodeGraph::DrawVariableListProp(Ref<IProperty> prop)
{
	ImDrawList* drawlist = ImGui::GetWindowDrawList();
	
	ImGuiID id = prop->GetID();
	ImVec2 rectSize = ImVec2(30, 15);
	ImVec2 cursorpos = ImGui::GetCursorScreenPos() + ImGui::GetStyle().FramePadding;
	
	ImGui::PushID(id);
	ImGui::BeginGroup();
	
	//draw oval shape representing property
	drawlist->AddRectFilled(cursorpos, cursorpos + rectSize,
		ImGui::GetColorU32(prop->GetColor()), rectSize.x / 4.0f, ImDrawCornerFlags_All);
	
	ImGui::SetCursorPosX(rectSize.x + 20.0f);

	auto textSize = ImVec2(100.0f, 20.f);

	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(.1f, .1f, .1f, 1.0f));

	if (ImGui::Button(prop->GetName().c_str(), textSize + ImVec2(5, 5)))
	{
		if (m_SelectedObject && m_SelectedObject->GetObjectType() == EObjectType::Node)
		{
			ed::NodeId selectedNodes;
			while (ed::GetSelectedNodes(&selectedNodes, 1))
			{
				ed::DeselectNode(selectedNodes);
			}
		}

		m_SelectedObject = prop.get();
	}
	
	ImGui::PopStyleColor(2);

	ImGui::EndGroup();	

	if (ImGui::IsItemHovered() && prop->HasToolTip())
	{
		//Display tooltip
		ImGui::BeginTooltip();
		ImGui::TextUnformatted(prop->GetToolTip().c_str());
		ImGui::EndTooltip();
	}
	

	if (ImGui::BeginPopupContextItem("VaribaleContextMenu"))
	{
		for (unsigned int i = 0; i < TEnum<EVariableNodeType>::GetMax(); i++)
		{
			auto nodecreationtype = TEnum<EVariableNodeType>::GetStrings()[i];
			if (ImGui::Selectable(nodecreationtype.c_str(), false))
			{
				
			}
		}
	
		if (ImGui::Selectable("Delete Variable", false))
		{
			//destroy the prop
			prop->Destroy();
		}
	
		ImGui::EndPopup();
	}
	
	ImGui::PopID();
}

void NodeGraph::DrawSelectedPropertyWidget(NodeEditorObject* obj)
{
	if (ImGui::Begin("Details"))
	{

		if (obj)
		{
			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(5, 5));
			ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(.1f, .1f, .1f, 1.0f));

			auto item_width = ImGui::GetContentRegionAvail().x - 20.0f;
			ImGui::SetCursorPosX(10.0f);

			//ImGui::BeginVertical("details");

			switch (obj->GetObjectType())
			{
			case EObjectType::None:
				break;
			case EObjectType::Node:
				{
					
					
				}
				break;
			case EObjectType::Property:
				{
					IProperty* prop = Cast<IProperty>(obj);

					//ImGui::BeginHorizontal("prop");

					ImGui::SetNextItemWidth(item_width / 2.0f);
					auto str = prop->GetName();
					if (ImGui::InputText("##propertyname", & str))
					{
						prop->SetName(str);
					}

					ImGui::SetNextItemWidth(item_width / 2.0f);
					prop->DrawDetails();

					//ImGui::EndHorizontal();
				}
				break;
			default:
				break;
			}
			
			//ImGui::EndVertical();

			ImGui::PopStyleColor();
			ImGui::PopStyleVar();

		}
	}

	ImGui::End();
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
