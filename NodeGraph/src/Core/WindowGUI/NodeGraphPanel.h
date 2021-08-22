#pragma once

#include "Core/Core.h"

#include "ImGuiPanel.h"
#include "NodeGraph\NodeGraph.h"

class NodeGraphPanel : public ImGuiPanel
{

public:
	NodeGraphPanel(const std::string& label, ImGuiWindowFlags flags, ImGuiID id = 1, bool runtimecreated = false);

	void OnRenderMenuBar() override;

	void OnRenderWindow() override;

private:
	void ShowFileMenu();
	void ShowActionMenu();
	
	bool OnKeyPressed(KeyPressedEvent& e) override;
	bool OnKeyReleased(KeyReleasedEvent& e) override;
	bool OnMouseButtonPressed(MouseButtonPressedEvent& e) override;
	bool OnMouseButtonReleased(MouseButtonReleasedEvent& e) override;
	bool OnMouseMoved(MouseMovedEvent& e) override;
	bool OnMouseScrolled(MouseScrolledEvent& e) override;

	Ref<class NodeGraph> m_Nodegraph;

};