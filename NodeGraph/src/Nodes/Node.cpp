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

DataPin* Node::GetParameter(const std::string& name)
{
	auto& pair = std::find_if(m_DataPins.begin(), m_DataPins.end(), [name](const Ref<DataPin>& p)
	{
		return p->m_Name == name;
	});

	return (*pair).get();
}

DataPin* Node::GetParameter(int index)
{
	return  m_DataPins[index].get();
}

Pin* Node::GetPinWithID(ImGuiID id)
{
	auto& pair = std::find_if(m_Pins.begin(), m_Pins.end(), [id](const Ref<Pin>& p)
	{
		return p->GetID() == id;
	});

	return (*pair).get();
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
	m_Pins.push_back(expin);
}

void Node::OnDraw()
{
	BeginDraw();
	CustomDraw();
	EndDraw();
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

		auto prop = output->GetProperty();
		ImNodes::PushColorStyle(ImNodesCol_Pin, ImGui::GetColorU32(prop->GetColor()));

		if (output->m_Type == ImNodesAttributeType_Output)
		{
			ImNodes::BeginOutputAttribute(output->GetID());
			ImNodes::EndOutputAttribute();
		}
		else if (output->m_Type == ImNodesAttributeType_Input)
		{

			ImNodes::BeginInputAttribute(output->GetID());
			ImGui::TextUnformatted(output->m_Name.c_str()); ImGui::SameLine();

			if (!output->IsConnected())
			{
				ImGui::SetNextItemWidth(80.0f);
				output->GetProperty()->Draw();
			}

			ImNodes::EndInputAttribute();
		}

		ImNodes::PopColorStyle();
	}
}

void Node::CustomDraw()
{
	

	
}


