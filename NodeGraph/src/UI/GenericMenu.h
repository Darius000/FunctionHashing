#pragma once

#include "Core.h"

namespace UI
{
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

	private:
		EngineEvent<> OnMenuItemSelected;

		std::string m_Text = "MenuItem";

		friend class GenericMenu;
	};

	class GenericMenu
	{
	public:

		GenericMenu(const std::string& menuName);

		void AddMenuItem(const MenuItem& menuItem);

		void RemoveMenuItem(const std::string& itemName);

		bool ShowAsContext();

		void OpenMenu();

	protected:
		bool Context();

	
	private:

		void DrawMenuItems();

		virtual void DrawMenuItem(const MenuItem& item);

	private:
		std::vector<MenuItem> m_ItemsList;

		std::string m_Name;

	public:
		float m_Padding = 5.0f;

	};
}