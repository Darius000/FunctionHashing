#include "GraphLayer.h"
#include "imgui-node-editor/imgui_node_editor.h"
#include "WindowGUI/NodeGraphPanel.h"
#include "Core/ImGui/LogPanel.h"
#include "WindowGUI/NodeListPanel.h"
#include "WindowGUI/ObjectDetailsPanel.h"
#include "WindowGUI/BlackBoardView.h"
#include "AssetManager/AssetManager.h"


namespace ed = ax::NodeEditor;
static ed::EditorContext* g_Context = nullptr;

GraphLayer::GraphLayer()
	:Layer("GraphLayer")
{
	b_ShowDemoWindow = false;
}


void GraphLayer::OnAttach()
{
	AssetManager::LoadAssetsAtPath("resources");

	g_Context = ed::CreateEditor();

	auto log = m_WindowStack.OpenPanel<LogPanel>("Log", ImGuiWindowFlags_None);
	auto graph = m_WindowStack.OpenPanel<NodeGraphPanel>("Node Graph", ImGuiWindowFlags_MenuBar);
	auto nodelist = m_WindowStack.OpenPanel<NodeListPanel>(ImGuiWindowFlags_None);
	auto details = m_WindowStack.OpenPanel<ObjectDetailsPanel>();
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

void GraphLayer::OnUpdate(float deltaTime)
{
	
}

void GraphLayer::OnImGuiRender()
{
	ed::SetCurrentEditor(g_Context);

	static bool dockSpaceOpen = true;
	static bool opt_fullscreen_persistant = true;
	static ImGuiDockNodeFlags opt_flags = ImGuiDockNodeFlags_None;
	bool opt_fullscreen = opt_fullscreen_persistant;

	ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
	if (opt_fullscreen)
	{
		ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->Pos);
		ImGui::SetNextWindowSize(viewport->Size);
		ImGui::SetNextWindowViewport(viewport->ID);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
		window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
	}

	if (opt_flags & ImGuiDockNodeFlags_PassthruCentralNode)
		window_flags |= ImGuiWindowFlags_NoBackground;

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::Begin("DockSpace Demo", &dockSpaceOpen, window_flags);
	ImGui::PopStyleVar();

	if (opt_fullscreen)
		ImGui::PopStyleVar(2);

	// Dockspace
	ImGuiIO& io = ImGui::GetIO();
	ImGuiStyle& style = ImGui::GetStyle();
	style.WindowMinSize.x = 150.0f;
	if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
	{
		ImGuiID dockspace_id = ImGui::GetID("MyDockspace");
		ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), opt_flags);
	}


	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::MenuItem("Show ImGui Demo Window")) b_ShowDemoWindow = true;
		ImGui::EndMainMenuBar();
	}

	//DEMO WINDOW IMGUI 
	if (b_ShowDemoWindow) ImGui::ShowDemoWindow(&b_ShowDemoWindow);

	m_WindowStack.Update();

	ed::SetCurrentEditor(nullptr);
}

void GraphLayer::ProcessEvents(Event& e)
{
	m_WindowStack.ExecutePanelEvents(e);
}
