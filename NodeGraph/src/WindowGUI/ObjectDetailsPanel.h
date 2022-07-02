#pragma once

#include "ImGui/ImGuiPanel.h"

class BaseObject;

class ObjectDetailsPanel : public ImGuiPanel
{
public:

	ObjectDetailsPanel(ImGuiWindowFlags flags = ImGuiWindowFlags_None, ImGuiID id = 1);

	void OnRenderMenuBar() override;

	void OnRenderWindow() override;

private:

	void DrawSelectedObj();
};