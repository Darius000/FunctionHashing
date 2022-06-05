#pragma once

#include "ImGui/ImGuiPanel.h"


class ObjectDetailsPanel : public ImGuiPanel
{
public:

	ObjectDetailsPanel(ImGuiWindowFlags flags = ImGuiWindowFlags_None, ImGuiID id = 1);

	void OnRenderMenuBar() override;

	void OnRenderWindow() override;

	RetEngineEvent<class NodeEditorObject*> OnGetSelectedObject;

private:

	void DrawSelectedObj();
};