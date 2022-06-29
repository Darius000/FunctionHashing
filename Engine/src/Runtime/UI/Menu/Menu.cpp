#include "PCH.h"
#include "Menu.h"
#include "Utilities/VectorUtilities.h"
#include "imgui.h"

Menu::Menu(const std::string& menuName)
	:m_Name(menuName)
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

void Menu::OpenMenu()
{
	ImGui::OpenPopup(m_Name.c_str());
}

bool Menu::ShowAsContext()
{
	return Context();
}

bool Menu::Context()
{
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(m_Padding, m_Padding));
	bool opened = ImGui::BeginPopup(m_Name.c_str());

	if (opened)
	{
		DrawMenuItems();

		ImGui::EndPopup();
	}

	ImGui::PopStyleVar();

	return opened;
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