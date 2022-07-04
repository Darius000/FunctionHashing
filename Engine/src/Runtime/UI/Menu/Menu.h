#pragma once

#include "Events/EventDelegate.h"

struct MenuItem
{

	MenuItem(const std::string& text = "", std::function<void()> onselected = nullptr)
	{
		m_Text = text;

		if (onselected)
		{
			OnMenuItemSelected += onselected;
		}
	}

protected:
	EngineEvent<> OnMenuItemSelected;

	std::string m_Text = "MenuItem";

	friend class Menu;
};

class Menu
{
public:

	Menu(const std::string& menuName);

	void AddMenuItem(const MenuItem& menuItem);

	void RemoveMenuItem(const std::string& itemName);

	void Show();

	RetEngineEvent<bool> m_CanOpenMenuCallBack;

private:

	void DrawMenuItems();

	virtual void DrawMenuItem(const MenuItem& item);

private:
	std::vector<MenuItem> m_ItemsList;

	std::string m_Name;

public:
	float m_Padding = 5.0f;

};