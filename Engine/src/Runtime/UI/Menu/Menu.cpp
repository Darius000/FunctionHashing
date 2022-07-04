#include "PCH.h"
#include "Menu.h"
#include "Utilities/VectorUtilities.h"
#include "imgui.h"

Menu::Menu(const std::string& menuName, const std::vector<MenuItem>& menuItems)
	:m_Name(menuName), m_ItemsList(menuItems)
{

}

void Menu::AddMenuItem(const MenuItem& menuItem)
{
	m_ItemsList.push_back(menuItem);
}

void Menu::RemoveMenuItem(const std::string& itemName)
{
	VectorUtilities::Remove(m_ItemsList, [&](MenuItem& item) {
		return item.m_Text == itemName;
		});
}

void Menu::Show()
{
	if (m_CanOpenMenuCallBack.Invoke())
	{
		ImGui::OpenPopup(m_Name.c_str());
	}

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(m_Padding, m_Padding));
	ImGui::PushStyleColor(ImGuiCol_PopupBg, ImVec4(.2f, .2f, .2f, 1.0f));
	bool opened = ImGui::BeginPopup(m_Name.c_str());

	if (opened)
	{
		DrawMenuItems();

		ImGui::EndPopup();
	}

	ImGui::PopStyleColor();
	ImGui::PopStyleVar();
}

void Menu::DrawMenuItems()
{
	for (auto& item : m_ItemsList)
	{
		DrawMenuItem(item);
	}
}
void Menu::DrawMenuItem(const MenuItem& item)
{
	if (ImGui::MenuItem(item.m_Text.c_str()))
	{
		item.OnMenuItemSelected.Invoke();

	}

}