#include "PCH.h"
#include "NodeGraph.h"
#include "Registry\NodeRegistry.h"
#include "DataTypes/Property.h"
#include "DataTypes/TypeDescriptor.h"
#include "DataTypes/DataTypeRegistry.h"
#include "Nodes/VariableNodeInterface/VariableNodeInterface.h"
#include "Core/Events/MouseEvent.h"
#include "NodeEditor/imgui_node_editor.h"
#include "imgui.h"
#include "Core\Debug\Instrumentor.h"
#include "NodeBuilder.h"

namespace ed = ax::NodeEditor;

NodeGraph::NodeGraph()
{
	PROFILE_FUNCTION();
	m_OpenNodePopup = false;
}

void NodeGraph::Draw()
{
	PROFILE_FUNCTION();

	if (ImGui::Begin("Nodes"))
	{
		DrawNodeList();

		ImGui::End();
	}

	DrawVariableList();

	DrawSelectedPropertyWidget(m_SelectedObject);

	ed::PushStyleVar(ed::StyleVar_PinRadius, 6.0f);
	ed::PushStyleVar(ed::StyleVar_PinBorderWidth, 2.0f);
	ed::PushStyleVar(ed::StyleVar_LinkStrength, 100.0f);

	ed::Begin("Nodes");

	DrawNodes();

	DrawNodeLinks();

	//handle new links
	if (ed::BeginCreate())
	{
		//does editor want to create new link?
		ed::PinId start, end;
		if (ed::QueryNewLink(&start, &end))
		{
			if (start && end)//if its valid accept link
			{
				Pin* startpin  = FindPind((ImGuiID)start.Get());
				Pin* endpin = FindPind((ImGuiID)end.Get());

				if (startpin && endpin)
				{
					TEnum<EPinRejectReason> rejectreason = EPinRejectReason::None;
					bool valid = startpin->IsValidConnection(*endpin, rejectreason) &&
					endpin->IsValidConnection(*startpin, rejectreason);

					auto show_label = [rejectreason]() {
						auto label = rejectreason.ToString().c_str();
						auto drawlist = ImGui::GetWindowDrawList();
						auto pos = ImGui::GetMousePos();

						auto size = ImGui::CalcTextSize(label);

						ImGui::SetCursorScreenPos(pos);
						
						drawlist->AddRectFilled(pos, pos + size, ImColor(ImGuiExtras::Black) );

						ImGui::TextUnformatted(label);
					};


					if ( valid )
					{
						//true when mouse button released
						if (ed::AcceptNewItem())
						{
							startpin->m_Connections++;
							endpin->m_Connections++;

							auto newlink = new Link(start, end);
							m_NodeLinks.emplace(newlink->GetID(), Scope<Link>(newlink));
						}
					}
					else
					{
						
						show_label();
						ed::RejectNewItem({1, 0, 0 ,1}, LinkBuilder::m_LinkThickness);
					}
				}
				
			}
		}

		ed::PinId pinId = 0;
		if (ed::QueryNewNode(&pinId))
		{
			if (ed::AcceptNewItem())
			{
				ImGui::OpenPopup("Node Context menu");
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
				auto& link = m_NodeLinks.find((ImGuiID)deletedlinkid.Get());
				if ( link != m_NodeLinks.end())
				{
					Pin* startpin = FindPind((ImGuiID)link->second->m_StartPin.Get());
					Pin* endpin = FindPind((ImGuiID)link->second->m_EndPin.Get());

					if (startpin && endpin)
					{
						startpin->m_Connections--;
						endpin->m_Connections--;
					}

					m_NodeLinks[(ImGuiID)deletedlinkid.Get()]->Destroy();
					break;
				}
			}
		}

		ed::NodeId deletednodeid;
		while (ed::QueryDeletedNode(&deletednodeid))
		{
			if (ed::AcceptDeletedItem())
			{
				ImGuiID id = (ImGuiID)deletednodeid.Get();
				if (m_Nodes.find(id) != m_Nodes.end())
				{
					m_Nodes[id]->Destroy();
					break;
				}
			}
		}
	}
	ed::EndDelete();

	if (ed::ShowBackgroundContextMenu())
	{
		ImGui::OpenPopup("Node Context menu");
	}

	if (ImGui::BeginPopup("Node Context menu"))
	{
		auto& list = NodeCatgeories::GetCategoryList();

		DrawCategory("Create Node Popup", list, [this]() {
			ImGui::CloseCurrentPopup();
			m_OpenNodePopup = false;
		});

		ImGui::EndPopup();
	}

	ed::NodeId selectednode;
	ed::GetSelectedNodes(&selectednode, 1);

	if (selectednode != ed::NodeId::Invalid)
	{
		m_SelectedObject = m_Nodes[(ImGuiID)selectednode.Get()].get();
	}

	ed::End();
	ed::PopStyleVar(3);

	if (ImGui::BeginPopupContextItem("Context Menu"))
	{
		auto& list = NodeCatgeories::GetCategoryList();

		DrawCategory("Create Node Popup", list, [this]() {
			ImGui::CloseCurrentPopup();
			m_OpenNodePopup = false;
		});

		ImGui::EndPopup();
	}



}


void NodeGraph::DrawCategory(const std::string& id, const CategoryList& list)
{
	float width = ImGui::GetWindowContentRegionWidth();
	for (auto& leaf : list.m_Leafs)
	{	
		auto name = leaf + "##" + id;
		if (ImGui::TreeNodeEx(name.c_str(), ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Leaf))
		{
			ImGui::TreePop();
		}

		if (ImGui::IsItemClicked((int)EMouseButton::Left))
		{
			Instantiate(leaf);
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
			DrawCategory(id, *cat.second);
			ImGui::TreePop();
			
		}
	}
}

template<typename Pred>
void NodeGraph::DrawCategory(const std::string& id, const struct CategoryList& list, Pred pred)
{
	float width = ImGui::GetWindowContentRegionWidth();
	for (auto& leaf : list.m_Leafs)
	{
		auto name = leaf + "##" + id;
		if (ImGui::TreeNodeEx(name.c_str(), ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Leaf))
		{
			ImGui::TreePop();
		}

		if (ImGui::IsItemClicked((int)EMouseButton::Left))
		{
			Instantiate(leaf);

			pred();
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
			DrawCategory(id, *cat.second, pred);
			ImGui::TreePop();

		}
	}
}

Pin* NodeGraph::FindPind(ImGuiID id)
{
	Pin* pin  = nullptr;
	for (auto& node : m_Nodes)
	{
		pin = node.second->FindPin(id);
		if(pin) break;
	}

	return pin;
}

void NodeGraph::DrawNodeList()
{	
	auto& list = NodeCatgeories::GetCategoryList();

	ImGui::BeginGroup();
	DrawCategory("Node List", list);
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

	if (ImGui::BeginPopupContextItem("Nodes"))
	{
		const ImVec2 click_pos = ImGui::GetMousePosOnOpeningCurrentPopup();
		DrawCategory("Node Context Menu", NodeCatgeories::GetCategoryList());

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
				Instantiate(nodecreationtype + prop->GetTypeName(), prop);
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

			auto item_width = ImGui::GetContentRegionAvailWidth() - 20.0f;
			ImGui::SetCursorPosX(10.0f);

			ImGui::BeginVertical("details");

			switch (obj->GetObjectType())
			{
			case EObjectType::None:
				break;
			case EObjectType::Node:
				{
					Node* node = Cast<Node>(obj);
					for (auto pin : node->m_Pins)
					{
						if (pin->GetPinType() == EPinType::DataPin && pin->pinKind == ed::PinKind::Input)
						{
							ImGui::BeginHorizontal(pin->GetID());
							ImGui::TextUnformatted(pin->GetName().c_str());
							pin->GetProperty()->DrawDetails();
							ImGui::EndHorizontal();
						}
					}
				}
				break;
			case EObjectType::Property:
				{
					IProperty* prop = Cast<IProperty>(obj);

					ImGui::BeginHorizontal("prop");

					ImGui::SetNextItemWidth(item_width / 2.0f);
					auto str = prop->GetName();
					if (ImGui::InputText("##propertyname", & str))
					{
						prop->SetName(str);
					}

					ImGui::SetNextItemWidth(item_width / 2.0f);
					prop->DrawDetails();

					ImGui::EndHorizontal();
				}
				break;
			default:
				break;
			}
			
			ImGui::EndVertical();

			ImGui::PopStyleColor();
			ImGui::PopStyleVar();

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
			if (m_SelectedObject == it->second.get()) m_SelectedObject = nullptr;

			it = m_Nodes.erase(it);
		}
		else
		{
			auto& node = it->second;
			NodeBuilder builder(node.get());
			builder.DrawNode();
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
			auto& link = it->second;
			LinkBuilder builder(link.get());
			builder.Draw();
			++it;
		}
		else
		{
			
			it = m_NodeLinks.erase(it);
		}
	}
}
