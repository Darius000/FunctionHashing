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

	auto id = new_node->GetID();

	m_Nodes.push_back(MakeScope<class NodeElement>(new_node));

	ed::CenterNodeOnScreen((UINT64)id);
}

void NodeGraph::Draw()
{
	PROFILE_FUNCTION();

	DrawVariableList();

	ed::PushStyleVar(ed::StyleVar_PinRadius, 6.0f);
	ed::PushStyleVar(ed::StyleVar_PinBorderWidth, 2.0f);
	ed::PushStyleVar(ed::StyleVar_LinkStrength, 100.0f);

	ed::Begin("Nodes");


	//handle new links
	if (ed::BeginCreate())
	{
		//does editor want to create new link?
		ed::PinId start, end;
		if (ed::QueryNewLink(&start, &end))
		{
			if (start && end)//if its valid accept link
			{
				Pin* startpin = FindPind((Core::UUID)start.Get());
				Pin* endpin = FindPind((Core::UUID)end.Get());

				if (startpin && endpin)
				{
					TEnum<EPinRejectReason> rejectreason = EPinRejectReason::None;
					bool valid = CanConnectPins(startpin, endpin, rejectreason);

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
							m_NodeLinks.push_back(MakeScope<Link>(start, end));
						}
					}
					else
					{
						
						show_label();
						//ed::RejectNewItem({1, 0, 0 ,1}, LinkBuilder::m_LinkThickness);
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
				for (int i = 0; i < m_NodeLinks.size(); i++)
				{
					auto& link = m_NodeLinks[i];
					auto start = link->m_StartPin;
					auto end = link->m_EndPin;

					if (start == (ed::PinId)deletedlinkid.Get() || (ed::PinId)deletedlinkid.Get())
					{
						Helpers::Vector::Remove(m_NodeLinks, link);
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

		auto id = (ImGuiID)selectednode.Get();
		auto node = FindNodeByID(id);
		m_SelectedObject = node;
	}

	DrawNodes();

	DrawNodeLinks();


	ed::End();
	ed::PopStyleVar(3);
}


Pin* NodeGraph::FindPind(Core::UUID id)
{
	for (int i = 0; i < m_Nodes.size(); i++)
	{
		auto& node = m_Nodes[i];
		for (auto j = 0; j < node->GetNode()->GetPins().size(); j++)
		{
			auto& pin = node->GetNode()->GetPins()[i];

			if (pin->GetID() == id)
			{
				return pin.get();
			}
		}
	}

	return nullptr;
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

NodeEditorObject* NodeGraph::FindNodeByID(ImGuiID id) const
{
	for (auto& node_element : m_Nodes)
	{
		if (auto node = node_element.get()->GetNode(); node && (ImGuiID)node->GetID() == id)
		{
			return node;
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

bool NodeGraph::CanConnectPins(Pin* start, Pin* end, TEnum<EPinRejectReason>& rejectReason)
{
	bool sameTypes = start->GetPinType() == end->GetPinType();
	bool differentPinKinds = start->pinKind != end->pinKind;

	if (!sameTypes) rejectReason = EPinRejectReason::DifferentDataTypes;
	if (!differentPinKinds) rejectReason = EPinRejectReason::DifferentPinTypes;

	return sameTypes && differentPinKinds;
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
					Node* node = Cast<Node>(obj);
					for (auto& pin : node->GetPins())
					{
						if (pin->GetPinType() == EPinType::DataPin && pin->pinKind == ed::PinKind::Input)
						{
							//ImGui::BeginHorizontal((ImGuiID)pin->GetID());
							ImGui::TextUnformatted(pin->GetName().c_str());
							if(pin->GetProperty() && pin->m_Connections == 0) pin->GetProperty()->DrawDetails();
							//ImGui::EndHorizontal();
						}
					}
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

void NodeGraph::DrawNodes()
{
	for (size_t i = 0; i < m_Nodes.size(); i++)
	{
		auto& nodeElement = m_Nodes[i];

		nodeElement->DrawElement(ImGui::GetWindowDrawList());
	}
}


void NodeGraph::DrawNodeLinks()
{
	//for (auto& it = m_NodeLinks.begin(); it != m_NodeLinks.end();)
	//{
	//	//if (!(*it).second->IsPendingDestroy())
	//	//{
	//	//	//auto& link = it->second;
	//	//	//LinkBuilder builder(link.get());
	//	//	builder.Draw();
	//	//	++it;
	//	//}
	//	//else
	//	//{
	//	//	
	//	//	it = m_NodeLinks.erase(it);
	//	//}
	//}
}
