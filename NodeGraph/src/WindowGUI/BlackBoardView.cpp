#include "BlackBoardView.h"
#include "Events/EventDelegate.h"
#include "AssetManager/AssetManager.h"
#include "Types/Color.h"
#include "Runtime/BaseObject/Selection.h"

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

void BlackBoardView::DrawKey(const Ref<BlackBoardKey>& key)
{
	auto name = key->GetName();
	Color image_color = Color();

	auto type = rttr::type::get(*key.get());
	auto meta_data = type.get_metadata("Color");
	if (meta_data)
	{
		image_color = meta_data.get_value<Color>();
	}

	auto region_size = ImVec2(ImGui::GetContentRegionAvail().x, 50.0f);
	ImGui::BeginHorizontal(name.c_str(), region_size);

	auto imageratio = s_CapsuleImage->GetWidth() / s_CapsuleImage->GetHeight();
	auto image_size = ImVec2(imageratio * 50.0f, imageratio * 50.0f);

	ImGui::Image(reinterpret_cast<ImTextureID>((uint64_t)s_CapsuleImage->GetRendererID()), image_size, { 0, 1 }, {1, 0}, image_color);



	ImGui::Spring(1, 1);

	if (ImGui::Selectable(name.c_str(), Selection::Get() == key))
	{
		Selection::Select(key);
	}


	ImGui::EndHorizontal();

	CreateContextMenu(key);

	/*if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_::ImGuiDragDropFlags_SourceAllowNullID))
	{
		ImGui::SetDragDropPayload("BLACKBOARDKEY", reinterpret_cast<const void*>(key.get()), sizeof(key.get()), ImGuiCond_Always);
		ImGui::EndDragDropSource();
	}*/

}

void BlackBoardView::CreateContextMenu(const Ref<BlackBoardKey>& key)
{
	auto options = rttr::type::get<EKeyContextMenuOptions>().get_enumeration();

	if (ImGui::BeginPopupContextItem("Key Context Menu"))
	{
		for (auto option : options.get_names())
		{
			EKeyContextMenuOptions value = options.name_to_value(option).get_value<EKeyContextMenuOptions>();
			if (ImGui::Selectable(option.data(), false))
			{
				OnOptionSelected.Invoke(key,value);
			}
		}

		ImGui::EndPopup();
	}
}

Ref<Texture> BlackBoardView::s_CapsuleImage = nullptr;

REFLECT_INLINE(EKeyContextMenuOptions)
{
	rttr::registration::enumeration<EKeyContextMenuOptions>("KeyContextMenuOptions")
		(
			rttr::value("Set", EKeyContextMenuOptions::Set),
			rttr::value("Get", EKeyContextMenuOptions::Get)
		);
}
