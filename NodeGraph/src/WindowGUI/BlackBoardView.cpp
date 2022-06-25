#include "BlackBoardView.h"
#include "Events/EventDelegate.h"
#include "AssetManager/AssetManager.h"

BlackBoardView::BlackBoardView(ImGuiID id)
	:ImGuiPanel("BlackBoard", ImGuiWindowFlags_None, id)
{
	s_CapsuleImage = AssetManager::Get<Texture>("Capsule.png");
}

void BlackBoardView::OnRenderWindow()
{
	//draw create key button


	auto blackboard = OnGetBlackBoard.Invoke();
	
	if (blackboard)
	{
		auto padding = ImGui::GetStyle().FramePadding.x;

		ImGui::BeginVertical("Keys");

		ImGui::BeginHorizontal("Keys Header");


		//draw header
		ImGui::Text("Keys");

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 1, 0, 1));

		ImGui::Spring(1, padding);

		//draw drop down
		bool addedkey = ImGui::Button("Add Key");
		bool changed = false;


		if (addedkey)
		{
			ImGui::OpenPopup("Key Types");
		}

		if (ImGui::BeginPopup("Key Types"))
		{
			for (auto type : rttr::type::get<BlackBoardKey>().get_derived_classes())
			{
				auto name = type.get_name().data();
				if (ImGui::Selectable(name, false))
				{
					auto key = blackboard->Create(name, type);
					blackboard->Add(key);
					changed |= true;
				}
			}
			ImGui::EndPopup();
		}


		ImGui::EndHorizontal();

		
		ImGui::BeginVertical("BlackBoard Keys", {}, 0.0f);
	
		//draw keys
		for (auto& item : blackboard->GetKeys())
		{
			DrawKey(item);
		}
		ImGui::EndVertical();
		
		ImGui::PopStyleColor();

		ImGui::EndVertical();
	}
}

void BlackBoardView::DrawKey(Ref<BlackBoardKey>& key)
{
	auto name = key->GetName();

	ImGui::BeginHorizontal(name.c_str(), {0,0},0.0f);

	ImGui::Image((void*)s_CapsuleImage->GetRenderID(), {40, 40});

	if (ImGui::Selectable(name.c_str(), m_SelectedKey == key.get(), 0, {0, 40}))
	{
		m_SelectedKey = key.get();
	}

	

	ImGui::EndHorizontal();
}

Ref<Texture> BlackBoardView::s_CapsuleImage = nullptr;