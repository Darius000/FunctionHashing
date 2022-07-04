#pragma once

#include "Events/EventDelegate.h"

struct MenuItem
{
	MenuItem() = default;

	MenuItem(const std::string& text = "", std::function<void()> onselected = nullptr)
	{
		m_Text = text;

		if (onselected)
		{
			OnMenuItemSelected += onselected;
		}
	}

	MenuItem(const MenuItem& other)
	{
		OnMenuItemSelected = other.OnMenuItemSelected;
		m_Text = other.m_Text;
	}

	MenuItem(MenuItem&& other) noexcept
	{
		OnMenuItemSelected = std::move(other.OnMenuItemSelected);
		m_Text = std::move(other.m_Text);
	}

	MenuItem& operator =(const MenuItem& other)
	{
		OnMenuItemSelected = other.OnMenuItemSelected;
		m_Text = other.m_Text;
		return *this;
	}

	MenuItem& operator =(MenuItem&& other) noexcept
	{
		OnMenuItemSelected = std::move(other.OnMenuItemSelected);
		m_Text = std::move(other.m_Text);
		return *this;
	}

protected:
	EngineEvent<> OnMenuItemSelected;

	std::string m_Text = "MenuItem";

	friend class Menu;
};

class Menu
{
public:

	Menu(const std::string& menuName, const std::vector<MenuItem>& menuItems = {});

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