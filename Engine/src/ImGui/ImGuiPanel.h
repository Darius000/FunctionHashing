#pragma once

#include "Core/Core.h"
#include "Core/Event.h"
#include "Events/KeyEvents.h"
#include "Events/MouseEvent.h"
#include "imgui.h"


class ImGuiPanel
{
public:
	ImGuiPanel() = default;
	ImGuiPanel(const std::string& label, ImGuiWindowFlags flags = ImGuiWindowFlags_None, ImGuiID id = 1 ,bool runtimecreated  = false);
	virtual ~ImGuiPanel();

public:
	virtual void OnUpdate(float deltatime) {};
	void OnRender();

protected:

	
	virtual void OnRenderMenuBar() {};
	virtual	void OnRenderWindow() = 0;
	virtual void OnFocused();
	virtual void OnUnFocused();

private:
	void OnBeginWindow();
	void OnEndWindow();

public:

	void Close();
	inline bool IsOpen() const { return m_IsOpen; }
	bool IsFocusedAndHoverd() const;

protected:
	ImVec2 m_WindowPadding;
	ImVec2 m_FramePadding;

	bool m_IsOpen = true;

	std::string m_Label;

	ImGuiWindowFlags m_Flags = 0;

	bool m_RuntimeCreated = false;

	bool b_IsFocused = false;
		
	bool b_IsHovered = false;

	ImGuiID m_ID;
};
