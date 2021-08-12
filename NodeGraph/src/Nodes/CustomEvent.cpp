#include "PCH.h"
#include "CustomEvent.h"

CustomEventNode::CustomEventNode()
{
	m_TitleColor = {1.0f, 0.0f, 0.0f, 0.3f};
	m_Color = {0.0f, 0.0f, 0.0f, 1.0f};

	AddExecutionPin(ImNodesAttributeType_Output);
}

void CustomEventNode::CustomDraw()
{
	Node::CustomDraw();

	
}

void CustomEventNode::OnDrawDetails()
{
	DrawAddPinButton();

	for (auto output : m_OutputParameters)
	{
		ImGui::PushID(output.second->m_Property->GetID());

		auto* propname = &output.second->m_Property->GetName();
		ImGui::SetNextItemWidth(80.0f);
		ImGui::InputText("##name", propname); ImGui::SameLine();

		output.second->m_Property->Draw(); 
		ImGui::PopID();
	}
}

void CustomEventNode::OnExecute()
{

}

DEFINE_REGISTER_NODE(CustomEventNode)

void CustomEventNode::DrawAddPinButton()
{
	float width = ImGui::GetContentRegionAvailWidth();

	ImGui::BeginGroup();

	if (ImGui::Button("Add New Property", { width, 20 }))
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
				AddDataPin(type->GetName(), PropertyType::Output, Ref<IProperty>(type));
			}
		}
		ImGui::EndPopup();
	}

	ImGui::EndGroup();
}
