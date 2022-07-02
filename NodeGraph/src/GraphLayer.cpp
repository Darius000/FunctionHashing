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

	//const uint8_t bluetex[] = { 0x00, 0xFF, 0x00, 0xFF};

	//m_ImageTest = MakeRef<BHive::Image>(1, 1, BHive::ImageFormat::RGBA, bluetex);
	//m_ImageTest->Resize(200, 200);
}

void GraphLayer::OnDetach()
{
	ed::DestroyEditor(g_Context);
}

void GraphLayer::OnUIRender()
{
	ed::SetCurrentEditor(g_Context);

	m_WindowStack.Update();

	/*ImGui::Begin("Image Test");

	ImGui::Image(m_ImageTest.get(), { (float)m_ImageTest->GetWidth(), (float)m_ImageTest->GetHeight() });

	ImGui::End();*/

	ed::SetCurrentEditor(nullptr);
}
