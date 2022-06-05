#pragma once

#include "ImGui/ImGuiPanel.h"
#include "Events/EventDelegate.h"


class NodeListPanel : public ImGuiPanel
{
public:
	NodeListPanel(ImGuiWindowFlags flags = 0, ImGuiID id = 1, bool runtimecreated = false);
	~NodeListPanel();

	void OnRenderMenuBar() override;

	void OnRenderWindow() override;

	void DrawCategory(std::string_view name, const struct CategoryList& item);

public:

	EngineEvent<std::string> OnMenuItemSelected;
};