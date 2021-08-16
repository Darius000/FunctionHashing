#include "PCH.h"
#include "NodeGraph.h"
#include "Core\Events\KeyCodes.h"
#include "Registry\NodeRegistry.h"
#include "imgui.h"
#include "imgui_internal.h"
#include "DataTypes/Property.h"
#include "DataTypes/TypeDescriptor.h"
#include "DataTypes/DataTypeRegistry.h"
#include "Nodes/VariableNodeInterface/VariableNodeInterface.h"
#include "Core/Events/KeyEvents.h"
#include "Core/Events/MouseEvent.h"
#include "NodeEditor/imgui_node_editor.h"
#include "imgui.h"
#include "Nodes\CommentNode.h"

namespace ed = ax::NodeEditor;

NodeGraph::NodeGraph()
{
	m_LinkThickness = 3.0f;
}

void NodeGraph::Draw()
{
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
					bool valid = startpin->IsValidConnection(*endpin) &&
					endpin->IsValidConnection(*startpin);

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
						ed::RejectNewItem({1, 0, 0 ,1}, m_LinkThickness);
					}
				}
				
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

	ed::End();
	ed::PopStyleVar(3);
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
				type->OnSelected.AddBinding([this](NodeEditorObject* obj)
				{
					if (m_SelectedObject != obj)
						m_SelectedObject = obj;
				});
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
		prop->OnSelected.Broadcast(prop.get());
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
			default:
				break;
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
					auto& str = prop->GetName();
					if (ImGui::InputText("##propertyname", & str))
					{
						prop->SetName(str);
					}

					ImGui::SetNextItemWidth(item_width / 2.0f);
					prop->DrawDetails();

					ImGui::EndHorizontal();
				}
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
			DrawNode(node.get());
		
			++it;
		}

	}
}

void NodeGraph::DrawNode(class Node* node)
{
	auto id = node->GetID();
	

	ed::PushStyleColor(ed::StyleColor_NodeBg, node->m_Color);
	ed::PushStyleVar(ed::StyleVar_NodeRounding, node->m_Rounding);
	ed::PushStyleVar(ed::StyleVar_PinBorderWidth, 3.0f);
	
	bool hasheader = node->GetNodeType() != ENodeType::Simple;
	bool hasInputs = node->m_NumInputs > 0;
	bool hasOutputs = node->m_NumOutputs > 0;
	
	ed::BeginNode(id);

	
	ImGui::PushID(id);

	ImGui::BeginVertical("node");

	if (hasheader)
	{
		ImGui::BeginHorizontal("header");

		if (node->GetNodeType() != ENodeType::Comment)
		{
			ImGui::TextUnformatted(node->GetTypeName().c_str());
		}
		else
		{
			auto comment = Cast<Comment>(node);
			ImGui::PushStyleColor(ImGuiCol_FrameBg, ImGuiExtras::Grey);
			ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImGuiExtras::Grey);
			ImGui::SetNextItemWidth(comment->m_Size.x);
			
			auto& str  = comment->m_Comment;
			if (ImGui::InputText("", &str))
			{
				comment->m_Comment = str;
			}
			ImGui::PopStyleColor(2);
		}
		
		ImGui::EndHorizontal();
		
	}
	
	ImGui::BeginHorizontal("content");
	if (node->GetNodeType() != ENodeType::Comment)
	{
		
		if (hasInputs)
		{
			DrawInputs(node);
		}
		else
		{
			ImGui::Spring();
		}

		if (!hasheader)
		{
			ImGui::BeginVertical("custom");
			ImGui::Spring();
			ImGui::TextUnformatted(node->GetTypeName().c_str());
			ImGui::Spring();
			ImGui::EndVertical();
		}

		if (hasOutputs)
		{
			DrawOutputs(node);
		}
	}
	else
	{
		auto comment = Cast<Comment>(node);
		ImGui::Dummy(comment->m_Size);
	}
	

	ImGui::EndHorizontal();
	
	ImGui::EndVertical();

	ImGui::PopID();


	ed::EndNode();

	ed::PopStyleVar(2);
	ed::PopStyleColor();

	if (hasheader)
	{
		auto drawlist = ed::GetNodeBackgroundDrawList(id);
		auto pos = ed::GetNodePosition(id);
		auto size = ed::GetNodeSize(id);
		drawlist->AddRectFilled(pos, pos + ImVec2(size.x, 28.0f), ImColor(node->m_TitleColor), node->m_Rounding, ImDrawCornerFlags_Top);

	}

	if (node->GetNodeType() == ENodeType::Comment)
	{
		auto comment = Cast<Comment>(node);
		DrawCommentResizeButton(comment);
	}
}

void NodeGraph::DrawPin(ImGuiID id, EPinType pintype, float size , const ImVec4& color, const ImVec4& innercolor)
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	if (window->SkipItems)
		return;

	ImGuiContext& g = *ImGui::GetCurrentContext();
	ImDrawList* drawlist = ImGui::GetWindowDrawList();
	auto pos = ImGui::GetCursorScreenPos();
	ImRect bounds;

	auto TotalSize = ImVec2(size, size) * 2;
	ImVec2 offset = ImVec2(size * 2.0f, 0.0f);
	auto borderwidth = ed::GetStyle().PinBorderWidth;

	switch (pintype)
	{
	case EPinType::None:
		break;
	case EPinType::DataPin:
	{
		
		drawlist->AddCircle(pos + TotalSize , size / 2.0f, ImColor(color), 0, borderwidth);
		drawlist->AddCircleFilled(pos + TotalSize, size / 2.0f, ImColor(innercolor));
		bounds = ImRect(pos, pos + TotalSize * 2.0f);
	}
	break;
	case EPinType::ExecutionPin:
	{
		auto pinpos = pos;
		float halfsize = size / 2.0f;
		ImVec2 points[] = {
			pinpos + TotalSize + ImVec2(-halfsize, halfsize),
			pinpos + TotalSize + ImVec2(0.0f, halfsize),
			pinpos + TotalSize + ImVec2(halfsize, 0.0f),
			pinpos + TotalSize + ImVec2(0.0f, -halfsize),
			pinpos + TotalSize + ImVec2(-halfsize, -halfsize)
		};

		drawlist->AddPolyline(points, 5,	ImColor(color), true, borderwidth);
		drawlist->AddConvexPolyFilled(points, 5, ImColor(innercolor));

		bounds = ImRect(pinpos, pinpos + TotalSize * 2.0f);
	}
	break;
	default:
		break;
	}

	ImGui::ItemSize(bounds);
	if(!ImGui::ItemAdd(bounds, id))
		return;

}

void NodeGraph::DrawPinTriangle(ImGuiID id, float size ,const ImVec4& color, const ImVec4& innercolor,
	const ImVec2& offset)
{
	ImGuiContext& g = *ImGui::GetCurrentContext();
	ImDrawList* drawlist = ImGui::GetWindowDrawList();
	auto pos = ImGui::GetCursorScreenPos();
	ImRect bounds;

	auto TotalSize = ImVec2(size, size) ;


	ImVec2 points[] =
	{
		pos + offset + ImVec2(0, 0),
		pos + offset + ImVec2(size , size / 2.0f),
		pos + offset + ImVec2(0.0f, size)
	};

	auto borderwidth = ed::GetStyle().PinBorderWidth;
	drawlist->AddTriangleFilled(points[0], points[1], points[2], ImColor(innercolor));
	drawlist->AddTriangle(points[0], points[1], points[2], ImColor(color), borderwidth);
	bounds = ImRect(pos + offset, pos + offset + TotalSize);

	//drawlist->AddRectFilled(bounds.Min, bounds.Max, ImColor(color)); //[DEBUG]

	ImGui::ItemSize(bounds);
	if(!ImGui::ItemAdd(bounds, id))
		return;


}

void NodeGraph::DrawInputs(class Node* node)
{

	auto style = ed::GetStyle();

	ImGui::BeginVertical("inputs");

	for (int i = 0; i < node->m_NumInputs; i++)
	{
		auto input = node->m_Inputs[i];
		auto id = input->GetID();

		IProperty* prop = input->GetProperty();

		auto color = prop ? prop->GetColor() : ImGuiExtras::Grey;
		auto innercolor = input->m_Connections > 0 ? prop ? prop->GetColor() : ImGuiExtras::White : ImGuiExtras::Black;

		auto txt = input->GetName();

		ImGui::BeginHorizontal(id);

		ed::BeginPin(id, input->pinKind);		
		DrawPin(id, input->GetPinType(), style.PinRadius, color , innercolor);
		ed::EndPin();

		if (input->GetPinType() == EPinType::DataPin)
		{
			ImGui::Spring(0,0);
			DrawPinTriangle(id, style.PinRadius,  color, innercolor, { -style.PinRadius, 0 });
			
			
		}
	
		if (!txt.empty()) {ImGui::Spring(); ImGui::TextUnformatted(txt.c_str()); ImGui::Spring();}

		if (prop && input->m_Connections == 0)
		{
			ImGui::PushStyleColor(ImGuiCol_FrameBg, ImGuiExtras::Grey);
			ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImGuiExtras::Grey);
			ImGui::Spring();
			ImGui::SetNextItemWidth(50.0f);
			prop->DrawDetails();
			ImGui::PopStyleColor(2);
		}

		ImGui::EndHorizontal();
	}

	ImGui::EndVertical();
}

void NodeGraph::DrawOutputs(class Node* node)
{
	auto style = ed::GetStyle();

	ImGui::BeginVertical("outputs");

	for (int i = 0; i < node->m_NumOutputs; i++)
	{
		auto input = node->m_Outputs[i];
		auto id = input->GetID();

		

		IProperty* prop = input->GetProperty();
		auto color = prop ? prop->GetColor() : ImGuiExtras::Grey;

		auto innercolor = input->m_Connections > 0 ? prop ? prop->GetColor() : ImGuiExtras::White : ImGuiExtras::Black;

		auto txt = input->GetName();

		ImGui::BeginHorizontal(id);

		ImGui::Spring();

		if (!txt.empty()) {  ImGui::TextUnformatted(txt.c_str()); ImGui::Spring(0.0f);}

		
		ed::BeginPin(id, input->pinKind);
			
		DrawPin(id, input->GetPinType(), style.PinRadius, color, innercolor );
		
		ed::EndPin();

		if (input->GetPinType() == EPinType::DataPin)
		{
			ImGui::Spring(0,0);

			DrawPinTriangle(id, style.PinRadius,  color, innercolor, {-style.PinRadius, 0});

		}


		ImGui::EndHorizontal();

	}

	ImGui::EndVertical();
}

void NodeGraph::DrawCommentResizeButton(class Comment* commentNode)
{
	auto id = commentNode->GetID();

	
	//Add Resize Button
	ImDrawList* drawlist = ed::GetNodeBackgroundDrawList(id);
	auto pos = ed::GetNodePosition(id);
	auto size = ed::GetNodeSize(id);

	ImVec2 buttonsize = { 30, 30 };
	ImRect rect = { pos + size - buttonsize, pos + size};
	drawlist->AddRectFilled(rect.Min, rect.Max, ImGui::GetColorU32({ .1f, .1f , .1f , .1f }));

	ImGui::ItemSize(rect);
	ImGui::ItemAdd(rect, id);

	bool hovered = ImGui::ItemHoverable(rect, id);
	hovered = ImGui::IsMouseHoveringRect(rect.Min, rect.Max, false);

	if (hovered)
	{
		auto window = ImGui::GetCurrentWindow();
		ImGui::SetHoveredID(id);
		ImGui::SetActiveID(id, window);
		ImGui::SetFocusID(id, window);

		ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeNWSE);

		if (ImGui::IsMouseDown(ImGuiMouseButton_Left))
		{
			auto deltaPos = ImGui::GetMouseDragDelta(ImGuiMouseButton_Left, 0.01f);
			commentNode->m_Size += deltaPos;
			ImGui::ResetMouseDragDelta(ImGuiMouseButton_Left);
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
			ed::Link(link->GetID(), link->m_StartPin, link->m_EndPin, ImGuiExtras::White, m_LinkThickness);
			++it;
		}
		else
		{
			
			it = m_NodeLinks.erase(it);
		}
	}
}


NodeEditorObject* NodeGraph::m_SelectedObject = nullptr;
