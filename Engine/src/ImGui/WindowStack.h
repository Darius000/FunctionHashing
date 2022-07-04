#pragma once

#include "ImGuiPanel.h"


class WindowStack
{
public:
	using Editors = std::unordered_map<ImGuiID, Scope<ImGuiPanel>>;

	WindowStack() ;
	~WindowStack();

public:
	template<typename T = ImGuiPanel, typename ... Args>
	T* OpenPanel( Args&& ... args)
	{
		ImGuiID PanelID = GetNewPanelID();
		auto newPanel = CreateNewPanel<T>(std::forward<Args>(args)...);
		m_Editors.emplace(PanelID, newPanel);
		return newPanel;
	}

	//Updates the window stack
	void Update(float deltatime);

	void RenderWindows();

private:
	Editors m_Editors;

	ImGuiID m_CurrentPanelID = 0;

private:

	void RenderCurrentWindow(ImGuiPanel* Panel);

	Scope<ImGuiPanel>& GetPanelFromID(ImGuiID PanelID);

	ImGuiID GetNewPanelID();

	template<typename T = ImGuiPanel, typename ... Args>
	T* CreateNewPanel(Args&& ... args)
	{
		return new T(std::forward<Args>(args)..., m_CurrentPanelID);
	}

};