#include "PCH.h"
#include "NodeGraphPanel.h"

NodeGraphPanel::NodeGraphPanel(const std::string& label, ImGuiWindowFlags flags, ImGuiID id, bool runtimecreated)
	:ImGuiPanel(label, flags, id, runtimecreated)
{
	m_WindowPadding = {0 , 0 };

	m_Nodegraph = MakeRef<NodeGraph>();
}

void NodeGraphPanel::OnRenderMenuBar()
{
	
}


void NodeGraphPanel::OnRenderWindow()
{
	m_Nodegraph->Draw();
}


bool NodeGraphPanel::OnKeyPressed(KeyPressedEvent& e)
{

	return false;
}

bool NodeGraphPanel::OnKeyReleased(KeyReleasedEvent& e)
{

	return false;
}

bool NodeGraphPanel::OnMouseButtonPressed(MouseButtonPressedEvent& e)
{
	return false;
}

bool NodeGraphPanel::OnMouseButtonReleased(MouseButtonReleasedEvent& e)
{
	return false;
}

bool NodeGraphPanel::OnMouseMoved(MouseMovedEvent& e)
{
	return false;
}

bool NodeGraphPanel::OnMouseScrolled(MouseScrolledEvent& e)
{
	return false;
}

