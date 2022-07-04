#pragma once

#include <Engine.h>
#include "NodeGraph/NodeGraph.h"
#include "ImGui/ImGuiPanel.h"

class NodeGraphPanel : public ImGuiPanel
{

public:
	NodeGraphPanel(const std::string& label, ImGuiWindowFlags flags, ImGuiID id = 1, bool runtimecreated = false);
	~NodeGraphPanel();

	void OnRenderMenuBar() override;

	void OnRenderWindow() override;

	void OnUpdate(float deltatime) override;

	Ref<NodeGraph>& GetGraph() { return m_Nodegraph; }

private:
	void ShowFileMenu();
	void ShowActionMenu();
	void SaveToRecentFiles(const std::string& filename);
	void SaveGraph(const std::string& filename);
	void LoadGraph(const std::string& filename);
	void SavePrefs();
	void LoadPrefs();
	
	Ref<class NodeGraph> m_Nodegraph;
	std::string m_LastFileUsed = "";
	std::vector<std::string> m_RecentFiles;
	bool m_OpenSaveModalPopup = false;

	std::string m_FileSaveFormat = "sav file (*.sav)|*.sav";
};