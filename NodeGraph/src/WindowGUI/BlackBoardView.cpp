#include "BlackBoardView.h"
#include "Events/EventDelegate.h"
#include "AssetManager/AssetManager.h"
#include "Types/Color.h"
#include "Runtime/BaseObject/Selection.h"

BlackBoardView::BlackBoardView(ImGuiID id)
	:ImGuiPanel("BlackBoard", ImGuiWindowFlags_None, id)
{
	s_CapsuleImage = AssetManager::Get<Texture>("Capsule.png");

	OnOptionSelected += [&](const Ref<BlackBoardKey>& key, const EKeyContextMenuOptions& option) {
		if (option == EKeyContextMenuOptions::Delete)
		{
			if (auto blackboard = OnGetBlackBoard.Invoke())
			{
				blackboard->Remove(key);
			}
		}
	};
}

void BlackBoardView::OnRenderWindow()
{
	//draw create key button


	auto blackboard = OnGetBlackBoard.Invoke();
	
	if (blackboard)
	{
		auto padding = ImGui::GetStyle().FramePadding.x;

		ImGui::BeginVertical("Keys", ImGui::GetContentRegionAvail());

		//Spring();

		ImGui::BeginHorizontal("Keys Header");

		Spring(0.0f, 1.0f);

		//draw header
		ImGui::Text("Keys");

		Spring(1.f, 1.0f);

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 1, 0, 1));


		//draw drop down
		bool addedkey = ImGui::Button("Add Key");

		Spring(-1.0f, 1.0f);


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
		
		Spring(0.0f, 0.0f);

		Spring(0.0f, 1.0f);

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
	if (key == nullptr) return;

	auto name = key->GetName();
	Color image_color = Color();

	auto type = rttr::type::get(*key.get());
	auto meta_data = type.get_metadata("Color");
	if (meta_data)
	{
		image_color = meta_data.get_value<Color>();
	}

	auto region_size = ImVec2(ImGui::GetContentRegionAvail().x, 50.0f);
	ImGui::BeginHorizontal(name.c_str());

	auto imageratio = s_CapsuleImage->GetWidth() / s_CapsuleImage->GetHeight();
	auto image_size = ImVec2(imageratio * 50.0f, imageratio * 50.0f);

	ImGui::Image(reinterpret_cast<ImTextureID>((uint64_t)s_CapsuleImage->GetRendererID()), image_size, { 0, 1 }, {1, 0}, image_color);



	Spring(1, 1);

	if (ImGui::Selectable(name.c_str(), Selection::Get() == key))
	{
		Selection::Select(key);
	}


	ImGui::EndHorizontal();

	CreateContextMenu(key);


}

void BlackBoardView::CreateContextMenu(const Ref<BlackBoardKey>& key)
{
	auto options = rttr::type::get<EKeyContextMenuOptions>().get_enumeration();

	if (ImGui::BeginPopupContextItem(("Key Context Menu ##" + key->GetName()).c_str()))
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

void BlackBoardView::Spring(float w, float s)
{
	ImGui::Spring(w, s);

	/*ImGui::GetWindowDrawList()->AddRect(
		ImGui::GetItemRectMin(), ImGui::GetItemRectMax(), IM_COL32(255, 0, 0, 255));*/
}

Ref<Texture> BlackBoardView::s_CapsuleImage = nullptr;

REFLECT_INLINE(EKeyContextMenuOptions)
{
	rttr::registration::enumeration<EKeyContextMenuOptions>("KeyContextMenuOptions")
		(
			rttr::value("Delete", EKeyContextMenuOptions::Delete),
			rttr::value("Set", EKeyContextMenuOptions::Set),
			rttr::value("Get", EKeyContextMenuOptions::Get)
		);
}
