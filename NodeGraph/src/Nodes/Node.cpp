#include "PCH.h"
#include "Node.h"
#include "ImNodes/imnodes.h"
#include "ImNodes/imnodes_internal.h"

Node::Node()
{
	m_Color = { .4f, .4f, .4f, .5f };
	m_TitleColor = {.6f, .6f, .6f, .5f};
	m_TitleStyle = ETitleStyle_::Default;
	m_Rounding = ImNodes::GetStyle().NodeCornerRounding;
	m_DefaultSize = {150.0f, 50.0f};
}

PropertyWrapper* Node::GetParameter(const std::string& name)
{
	return m_Parameters[name].get();
}

PropertyWrapper* Node::GetParameterWithID(ImGuiID id)
{
	auto& pair = std::find_if(m_Parameters.begin(), m_Parameters.end(), [id](const auto& p)
	{
		return p.second->m_Property->GetID() == id;
	});

	return pair->second.get();
}

std::vector<ExecutionPin*> Node::GetExecutionPinsByType(ImNodesAttributeType_ type) const
{
	std::vector<ExecutionPin*> matches;
	for (auto& exexpin : m_ExecPins)
	{
		if (exexpin->m_Type == type)
		{
			auto pin = exexpin.get();
			matches.push_back(pin);
		}
	}

	return matches;
}

void Node::AddExecutionPin(ImNodesAttributeType_ type)
{
	auto expin = MakeRef<ExecutionPin>(type, this);
	m_ExecPins.push_back(expin);
}

void Node::OnDraw()
{
	BeginDraw();
	CustomDraw();
	EndDraw();
}

void Node::OnDrawDetails()
{
	for (auto input : m_InputParameters)
	{
		
		input.second->m_Property->Draw(); ImGui::SameLine();
		ImGui::Text(input.first.c_str()); 
	}
}

void Node::Execute()
{
	OnExecute();

	auto pins = GetExecutionPinsByType(ImNodesAttributeType_Output);
	auto next = pins[0]->m_Next;
	if (next)
		next->Execute();
}

void Node::BeginDraw()
{
	auto bordercolor = m_IsSelected ? ImVec4(1, 1, 0, 1) : ImVec4(1, 1, 1, 1);

	ImNodes::PushColorStyle(ImNodesCol_TitleBar, ImGui::GetColorU32(m_TitleColor));
	ImNodes::PushColorStyle(ImNodesCol_TitleBarHovered, ImGui::GetColorU32(m_TitleColor));
	ImNodes::PushColorStyle(ImNodesCol_TitleBarSelected, ImGui::GetColorU32(m_TitleColor));
	ImNodes::PushColorStyle(ImNodesCol_NodeBackground, ImGui::GetColorU32(m_Color));
	ImNodes::PushColorStyle(ImNodesCol_NodeBackgroundHovered, ImGui::GetColorU32(m_Color));
	ImNodes::PushColorStyle(ImNodesCol_NodeBackgroundSelected, ImGui::GetColorU32(m_Color));
	ImNodes::PushColorStyle(ImNodesCol_NodeOutline, ImGui::GetColorU32(bordercolor));
	ImNodes::PushStyleVar(ImNodesStyleVar_NodeCornerRounding, m_Rounding);

	ImNodes::BeginNode(GetID());
	
	if (m_TitleStyle == ETitleStyle_::Default)
	{
		ImNodes::BeginNodeTitleBar();
		ImGui::TextUnformatted(GetTypeName().c_str());
		ImNodes::EndNodeTitleBar();
		
	}
}

void Node::EndDraw()
{
	DrawDataPins();

	if (GetParameters().size() == 0)
	{
		ImGui::Dummy(m_DefaultSize);
	}

	ImNodes::EndNode();

	m_IsSelected = ImNodes::IsNodeSelected(GetID());

	if (ImGui::IsMouseReleased(ImGuiMouseButton_Left) && ImGui::IsItemHovered())
	{
		OnSelected.Broadcast(this);
	}

	if (ImGui::BeginPopupContextItem("Actions"))
	{
		if (ImGui::Selectable("Delete"))
		{
			Destroy();
		}
		if (ImGui::Selectable("Execute"))
		{
			Execute();
		}

		ImGui::EndPopup();
	}

	ImNodes::PopColorStyle();
	ImNodes::PopColorStyle();
	ImNodes::PopColorStyle();
	ImNodes::PopColorStyle();
	ImNodes::PopColorStyle();
	ImNodes::PopColorStyle();
	ImNodes::PopColorStyle();
	ImNodes::PopStyleVar();

}

void Node::DrawDataPins()
{
	std::string next = "";
	ImNodes::PushColorStyle(ImNodesCol_Pin, ImGui::GetColorU32(ImVec4(.5f, .5f, .5f, 1)));
	for (Ref<ExecutionPin>& pin : m_ExecPins)
	{
		ImGui::SetWindowFontScale(3.0f);
		ImVec2 pos = ImNodes::GetNodeScreenSpacePos(GetID());
		ImGui::SetCursorScreenPos(pos);
		next = pin->m_Next ? std::to_string(pin->m_Next->GetID()) : "";
		auto drawlist = ImGui::GetWindowDrawList();
		ImGui::TextUnformatted(next.c_str());
		ImGui::SetWindowFontScale(1.0f);

		if (pin->m_Type == ImNodesAttributeType_Input)
		{
			ImNodes::BeginInputAttribute(pin->GetID());
			ImNodes::EndInputAttribute();
		}
		else if (pin->m_Type == ImNodesAttributeType_Output)
		{
			ImNodes::BeginOutputAttribute(pin->GetID());
			ImNodes::EndOutputAttribute();
		}
	}
	ImNodes::PopColorStyle();

	for (auto& output : GetParameters())
	{

		auto prop = output.second->m_Property;
		ImNodes::PushColorStyle(ImNodesCol_Pin, ImGui::GetColorU32(prop->GetColor()));

		if (output.second->m_PropertyType == PropertyType::Output)
		{
			ImNodes::BeginOutputAttribute(prop->GetID());
			ImGui::TextUnformatted(output.first.c_str());
			ImNodes::EndOutputAttribute();
		}
		else if (output.second->m_PropertyType == PropertyType::Input)
		{

			ImNodes::BeginInputAttribute(prop->GetID());
			ImGui::TextUnformatted(output.first.c_str()); ImGui::SameLine();

			if (!output.second->IsConnected())
			{
				ImGui::SetNextItemWidth(80.0f);
				prop->Draw();
			}

			ImNodes::EndInputAttribute();
		}

		ImNodes::PopColorStyle();
	}
}

void Node::CustomDraw()
{
	

	
}


