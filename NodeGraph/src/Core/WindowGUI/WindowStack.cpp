#include "PCH.h"
#include "WindowStack.h"


WindowStack::WindowStack()
	:m_CurrentPanelID(1)
{
	
}

WindowStack::~WindowStack()
{
	m_Editors.clear();
}

void WindowStack::Update()
{		
	
	RenderWindows();
}


void WindowStack::RenderWindows()
{
	for (auto it = m_Editors.begin(); it != m_Editors.end(); it++)
	{
		auto panel = it->second.get();
		auto id = it->first;

		RenderCurrentWindow(panel);
	}
}


void WindowStack::ExecutePanelEvents(Event& event)
{
	for (auto it = m_Editors.begin(); it != m_Editors.end(); it++)
	{
		auto panel = it->second.get();
		auto id = it->first;

		if (panel->IsFocusedAndHoverd())
			panel->OnRecieveEvent(event);
	}
}

void WindowStack::RenderCurrentWindow(ImGuiPanel* Panel)
{	
	Panel->OnRender();
}

Scope<ImGuiPanel>& WindowStack::GetPanelFromID(ImGuiID PanelID)
{
	Editors::iterator it = m_Editors.find(PanelID);
	return it->second;
}

ImGuiID WindowStack::GetNewPanelID()
{
	ImGuiID newID = m_CurrentPanelID++;

	return newID;	
}
