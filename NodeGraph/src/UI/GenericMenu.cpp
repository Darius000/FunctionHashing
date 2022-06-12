#include "PCH.h"
#include "GenericMenu.h"
#include "Helpers/Vectors/VectorHelper.h"
#include "imgui.h"

namespace UI
{
	GenericMenu::GenericMenu(const std::string& menuName)
		:m_Name(menuName)
	{

	}

	void GenericMenu::AddMenuItem(const MenuItem& menuItem)
	{
		m_ItemsList.push_back(menuItem);
	}

	void GenericMenu::RemoveMenuItem(const std::string& itemName)
	{
		Helpers::Vector::Remove(m_ItemsList, [&](MenuItem& item) {
			return item.m_Text == itemName;
		});
	}

	void GenericMenu::OpenMenu()
	{
		ImGui::OpenPopup(m_Name.c_str());
	}

	void GenericMenu::ShowAsContext()
	{
		Context();
	}

	void GenericMenu::Context()
	{
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(m_Padding, m_Padding));
		if (ImGui::BeginPopup(m_Name.c_str()))
		{
			
			DrawMenuItems();

			ImGui::EndPopup();
		}
		ImGui::PopStyleVar();
	}
	void GenericMenu::DrawMenuItems()
	{
		for (auto& item : m_ItemsList)
		{
			DrawMenuItem(item);
		}
	}
	void GenericMenu::DrawMenuItem(const MenuItem& item)
	{
		if (ImGui::MenuItem(item.m_Text.c_str()))
		{
			item.OnMenuItemSelected.Invoke();

		}
		
	}
}