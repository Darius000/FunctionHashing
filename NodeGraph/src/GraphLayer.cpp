#include "GraphLayer.h"
#include "imgui-node-editor/imgui_node_editor.h"
#include "WindowGUI/NodeGraphPanel.h"
#include "ImGui/LogPanel.h"
#include "WindowGUI/NodeListPanel.h"
#include "WindowGUI/ObjectDetailsPanel.h"
#include "WindowGUI/BlackBoardView.h"
#include "AssetManager/AssetManager.h"



namespace ed = ax::NodeEditor;
static ed::EditorContext* g_Context = nullptr;

GraphLayer::GraphLayer()
{
	
}


void GraphLayer::OnAttach()
{
	AssetManager::LoadAssetsAtPath("resources");

	g_Context = ed::CreateEditor();

	auto log = m_WindowStack.OpenPanel<LogPanel>("Log", ImGuiWindowFlags_None);
	auto graph = m_WindowStack.OpenPanel<NodeGraphPanel>("Node Graph", ImGuiWindowFlags_MenuBar);
	auto nodelist = m_WindowStack.OpenPanel<NodeListPanel>(ImGuiWindowFlags_None);
	auto details = m_WindowStack.OpenPanel<ObjectDetailsPanel>(ImGuiWindowFlags_None);
	auto nodeGraph = graph->GetGraph();
	auto blackboardview = m_WindowStack.OpenPanel<BlackBoardView>();

	nodelist->OnMenuItemSelected.AddBinding(BIND_EVENT(nodeGraph, NodeGraph::Instantiate));
	details->OnGetSelectedObject.AddBinding(BIND_EVENT(nodeGraph, NodeGraph::GetSelectedObject));
	blackboardview->OnGetBlackBoard.AddBinding(BIND_EVENT(nodeGraph, NodeGraph::GetBlackBoard));
}

void GraphLayer::OnDetach()
{
	ed::DestroyEditor(g_Context);
}

void GraphLayer::OnUIRender()
{
	ed::SetCurrentEditor(g_Context);

	ImGui::ShowAboutWindow();
	ImGui::ShowDemoWindow();

	m_WindowStack.Update();

	ed::SetCurrentEditor(nullptr);
}
