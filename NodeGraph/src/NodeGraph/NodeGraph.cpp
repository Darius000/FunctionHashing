#include "PCH.h"
#include "NodeGraph.h"
#include "Core\Events\KeyCodes.h"
#include "Registry\NodeRegistry.h"
#include "imgui.h"
#include "ImNodes/imnodes.h"
#include "imgui_internal.h"
#include "DataTypes/Property.h"
#include "DataTypes/TypeDescriptor.h"
#include "DataTypes/DataTypeRegistry.h"
#include "Nodes/VariableNodeInterface/VariableNodeInterface.h"
#include "Core/Events/KeyEvents.h"
#include "Core/Events/MouseEvent.h"
#include "Nodes/Node.h"
#include "NodeLink/NodeLink.h"

NodeGraph::NodeGraph()
{
	m_ID = s_ID++;
	ImNodes::GetIO().LinkDetachWithModifierClick.Modifier = &ImGui::GetIO().KeyAlt;
	ImNodes::PushAttributeFlag(ImNodesAttributeFlags_EnableLinkDetachWithDragClick);
}

void NodeGraph::Draw()
{
	if (ImGui::Begin("Nodes"))
	{
		DrawNodeList();

		ImGui::End();
	}

	DrawVariableList();

	DrawSelectedPropertyWidget(m_SelectedProperty);
	
	ImNodes::PushColorStyle(ImNodesCol_GridBackground, ImGui::GetColorU32(ImVec4(0 ,0 ,0 , 0)));
	ImNodes::BeginNodeEditor();

	DrawNodes();

	DrawNodeLinks();

	ImNodes::MiniMap(0.2f, ImNodesMiniMapLocation_BottomRight);
	ImNodes::EndNodeEditor();
	ImNodes::PopColorStyle();

	//check if editor is hovered before allowing context menu
	const bool editorhovered = IsEditorHovered();
	if(editorhovered) DrawNodeListContextMenu();

	//handle created links
	int start_attr_id, end_attr_id, start_node_id, end_node_id;
	if (ImNodes::IsLinkCreated(&start_node_id, &start_attr_id,  &end_node_id, &end_attr_id))
	{	
		auto& start_node = m_Nodes[start_node_id];
		auto& end_node = m_Nodes[end_node_id];
		auto* start_pin = start_node->GetPinWithID(start_attr_id);
		auto* end_pin = end_node->GetPinWithID(end_attr_id);

		if (CanPinsConnect(start_pin, end_pin))
		{
			start_pin->OnConnected(end_pin);
			end_pin->OnConnected(start_pin);
	
			auto link = new NodeLink(start_node_id, start_attr_id, end_node_id, end_attr_id);
			m_NodeLinks.emplace(link->GetID(), link);
		}
	}

	//handle destroyed links
	int destroyed_link_id;
	if (ImNodes::IsLinkDestroyed(&destroyed_link_id))
	{
		OnDestroyedLink(destroyed_link_id);
	}

	int item_hovered = 0;
	m_Item_Hovered = ImNodes::IsNodeHovered(&item_hovered);
	m_Item_Hovered |= ImNodes::IsAnyAttributeActive();
	m_Item_Hovered |= ImNodes::IsLinkHovered(&item_hovered);
	
	//Delete selected nodes when delete key is pressed
	if (ImGui::IsKeyPressed((int)EKeyCode::Delete))
	{
		DeleteSelectedNodes();
		DeleteSelectedLinks();
	}
		
}


void NodeGraph::RemoveNode(ImGuiID id)
{
	NodeGraph::NodeList::iterator node = m_Nodes.find(id);
	RemoveLinks(id);
	node->second->Destroy();
}


void NodeGraph::RemoveLinks(ImGuiID id)
{
	for (auto& link : m_NodeLinks)
	{
		if (link.second->IsConnected(id))
		{
			OnDestroyedLink(link.first);
			link.second->Destroy();
		}
	}
}

void NodeGraph::DrawCategory(const CategoryList& list, bool* selected)
{
	float width = ImGui::GetWindowContentRegionWidth();
	for (auto& leaf : list.m_Leafs)
	{	
		if (ImGui::TreeNodeEx(leaf.c_str(), ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Leaf))
		{
			ImGui::TreePop();
		}

		if (ImGui::IsItemClicked((int)EMouseButton::Left))
		{
			Instantiate(leaf);

			if(selected) *selected = true;
		}
		
		if (ImGui::IsItemHovered())
		{
			ImGui::BeginTooltip();
			ImGui::Text(leaf.c_str());
			ImGui::EndTooltip();
		}
		
	}

	for (auto& cat : list.m_SubCategories)
	{
		if (ImGui::TreeNodeEx(cat.first.c_str(), ImGuiTreeNodeFlags_DefaultOpen))
		{
			DrawCategory(*cat.second, selected);
			ImGui::TreePop();
		}
	}
}

const bool NodeGraph::IsEditorHovered() const
{
	const bool is_window_hovered_or_focused = ImGui::IsWindowHovered(ImGuiHoveredFlags_ChildWindows) || 
		ImGui::IsWindowFocused(ImGuiHoveredFlags_ChildWindows);

	return is_window_hovered_or_focused &&
		GImNodes->CanvasRectScreenSpace.Contains(ImGui::GetMousePos()) &&
		!IsAnyItemHovered();
}

const bool NodeGraph::IsAnyItemHovered() const
{
	return m_Item_Hovered;
}

void NodeGraph::DrawNodeList()
{	
	auto& list = NodeCatgeories::GetCategoryList();

	ImGui::BeginGroup();
	DrawCategory(list);
	ImGui::EndGroup();
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
				//clear selected property
				if (m_SelectedProperty == it->get()) m_SelectedProperty = nullptr;

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

void NodeGraph::DrawAddNewProperty()
{
	float width = ImGui::GetContentRegionAvailWidth();

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
	bool selected = false;

	if (ImGui::BeginPopupContextItem("Nodes"))
	{
		const ImVec2 click_pos = ImGui::GetMousePosOnOpeningCurrentPopup();
		DrawCategory(NodeCatgeories::GetCategoryList(), &selected);
		if (selected)
		{
			ImNodes::SetNodeScreenSpacePos(last_added_node, click_pos);
			ImGui::CloseCurrentPopup();
		}

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
		m_SelectedProperty = prop.get();
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
				Instantiate(nodecreationtype + prop->GetTypeName(), prop);
			}
		}
	
		if (ImGui::Selectable("Delete Variable", false))
		{
			

			//delete all nodes using this prop
			auto noderefs = prop->GetRefs();
			for (auto node_id : noderefs)
			{
				RemoveNode(node_id);
			}

			//destroy the prop
			prop->Destroy();
		}
	
		ImGui::EndPopup();
	}
	
	ImGui::PopID();
}

void NodeGraph::DrawSelectedPropertyWidget(IProperty* prop)
{
	if (ImGui::Begin("Details"))
	{
		float availablewidth = ImGui::GetWindowContentRegionWidth() / 2.0f;
		float itemwidth = 0;

		if (prop)
		{
			

			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(5, 5));
			ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(.1f, .1f, .1f, 1.0f));

			//change property name
			itemwidth = ImGui::CalcItemWidth() / 2.0f;
			ImGui::SetCursorPosX(availablewidth - itemwidth);

			auto str = prop->GetName();
			if (ImGui::InputText("Name", &str))
			{
				prop->SetName(str);
			}

			//change tooltip
			itemwidth = ImGui::CalcItemWidth() / 2.0f;
			ImGui::SetCursorPosX(availablewidth - itemwidth);

			auto tooltip = prop->GetToolTip();
			if (ImGui::InputText("Tooltip", &tooltip))
			{
				prop->SetToolTip(tooltip);
			}

			ImGui::PopStyleColor();
			ImGui::PopStyleVar();

			itemwidth = ImGui::CalcItemWidth() / 2.0f;
			ImGui::SetCursorPosX(availablewidth - itemwidth);

			m_SelectedProperty->Draw();
		}
	}

	ImGui::End();
}

void NodeGraph::DrawNodes()
{
	for (auto it = m_Nodes.begin(); it != m_Nodes.end();)
	{
		if (it->second->IsPendingDestroy())
		{
			RemoveNode(it->first);
			it = m_Nodes.erase(it);
		}
		else
		{
			it->second->Draw();
		
			++it;
		}

	}
}

void NodeGraph::DrawNodeLinks()
{
	for (auto& it = m_NodeLinks.begin(); it != m_NodeLinks.end();)
	{
		if (!(*it).second->IsPendingDestroy())
		{
			(*it).second->Draw();
			++it;
		}
		else
		{
			
			it = m_NodeLinks.erase(it);
		}
	}
}

bool NodeGraph::CanPinsConnect(Pin* s_attr, Pin* e_attr)
{
	//check if pin is the same type before creating

	return s_attr->CanConnect(e_attr);
}

void NodeGraph::DeleteSelectedNodes()
{
	auto num_selected_nodes = ImNodes::NumSelectedNodes();
	if (num_selected_nodes > 0)
	{
		std::vector<int> selectedNodes;
		selectedNodes.resize(num_selected_nodes);

		ImNodes::GetSelectedNodes(selectedNodes.data());

		for (auto nodeid : selectedNodes)
		{
			auto it = m_Nodes.find(nodeid);
			it->second->Destroy();
		}
	}
}

void NodeGraph::DeleteSelectedLinks()
{
	auto num_selected_links = ImNodes::NumSelectedLinks();
	if (num_selected_links > 0)
	{
		std::vector<int> selectedLinks;
		selectedLinks.resize(num_selected_links);

		ImNodes::GetSelectedLinks(selectedLinks.data());

		for (auto linkid : selectedLinks)
		{
			OnDestroyedLink(linkid);
		}
	}
}

void NodeGraph::OnDestroyedLink(const int link_id)
{
	auto& link = m_NodeLinks[link_id];
	auto startnodeid = link->m_Start_Ids.first;
	auto startpinid = link->m_Start_Ids.second;
	auto endnodeid = link->m_End_Ids.first;
	auto endpinid = link->m_End_Ids.second;
	auto* pinA = m_Nodes[startnodeid]->GetPinWithID(startpinid);
	auto* pinB = m_Nodes[endnodeid]->GetPinWithID(endpinid);
	if (pinA)
		pinA->OnDisConnected();
	if (pinB)
		pinB->OnDisConnected();

	link->Destroy();
}

struct IProperty* NodeGraph::m_SelectedProperty = nullptr;

ImGuiID NodeGraph::s_ID = 1;
