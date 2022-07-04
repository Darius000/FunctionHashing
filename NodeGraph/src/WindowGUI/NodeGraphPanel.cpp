#include "NodeGraphPanel.h"
#include "Core/Utils.h"
#include <fstream>
#include <filesystem>

NodeGraphPanel::NodeGraphPanel(const std::string& label, ImGuiWindowFlags flags, ImGuiID id, bool runtimecreated)
	:ImGuiPanel(label, flags, id, runtimecreated)
{
	LoadPrefs();

	m_WindowPadding = {0 , 0 };

	m_Nodegraph = MakeRef<NodeGraph>();
}

NodeGraphPanel::~NodeGraphPanel()
{
	SavePrefs();
}

void NodeGraphPanel::OnRenderMenuBar()
{
	
	if (ImGui::BeginMenu("File"))
	{
		ShowFileMenu();
		ImGui::EndMenu();
	}

	ShowActionMenu();
	
}


void NodeGraphPanel::OnRenderWindow()
{
	if (m_OpenSaveModalPopup)
	{
		ImGui::OpenPopup("Save?");
	}

	if (ImGui::BeginPopupModal("Save?", &m_OpenSaveModalPopup))
	{
		if (ImGui::Selectable("Yes"))
		{
			std::string filename = FileDialog::SaveFile(m_FileSaveFormat.c_str());	
			
			if (!filename.empty())
			{
				SaveGraph(filename);

				m_Nodegraph.reset();
				m_Nodegraph = MakeRef<NodeGraph>();
			}


			ImGui::CloseCurrentPopup(); 
			m_OpenSaveModalPopup = false;
		}

		if (ImGui::Selectable("No")) { 
			ImGui::CloseCurrentPopup(); 
			m_OpenSaveModalPopup = false; 
			m_Nodegraph.reset();
			m_Nodegraph = MakeRef<NodeGraph>();
		}

		ImGui::EndPopup();
	}

	m_Nodegraph->Draw();

}

void NodeGraphPanel::OnUpdate(float deltatime)
{
	m_Nodegraph->Update(deltatime);
}


void NodeGraphPanel::ShowFileMenu()
{
	std::string filename = "";

	if (ImGui::MenuItem("New"))
	{
		m_OpenSaveModalPopup = true;

	}

	if (ImGui::MenuItem("Load")) {
		filename = FileDialog::OpenFile(m_FileSaveFormat.c_str());

		if (!filename.empty())
		{
			LoadGraph(filename);
		}
		
	}

	if (ImGui::MenuItem("Save As...")) {
		filename = FileDialog::SaveFile(m_FileSaveFormat.c_str());

		if (!filename.empty())
		{
			SaveGraph(filename);
		}
		
	}

	if (ImGui::MenuItem("Save")) {

		if (!m_LastFileUsed.empty())
		{
			SaveGraph(m_LastFileUsed);
		}
		else
		{
			filename = FileDialog::SaveFile(m_FileSaveFormat.c_str());
			if (!filename.empty())
			{
				SaveGraph(filename);
			}
		}		
	}

	if (ImGui::BeginMenu("Recent Files..."))
	{

		for (auto file : m_RecentFiles)
		{
			if (ImGui::MenuItem(file.c_str()))
			{
				LoadGraph(file);
			}
		}

		ImGui::Separator();

		if (ImGui::MenuItem("Clear Recent...")) { m_RecentFiles.clear(); }

		ImGui::EndMenu();
	}


}

void NodeGraphPanel::ShowActionMenu()
{
	if (!m_Nodegraph->IsRunning())
	{
		if (ImGui::MenuItem("Play")) { m_Nodegraph->Run(); }
	}
	else
	{
		if (ImGui::MenuItem("Stop")) { m_Nodegraph->Stop(); }

		if (!m_Nodegraph->IsPaused())
		{
			if (ImGui::MenuItem("Pause")) { m_Nodegraph->Pause(); }
		}
		else
		{
			if (ImGui::MenuItem("Resume")) { m_Nodegraph->Resume(); }
		}
	}
}

void NodeGraphPanel::SaveToRecentFiles(const std::string& filename)
{
	auto it = std::find(m_RecentFiles.begin(), m_RecentFiles.end(), filename);

	if (it == m_RecentFiles.end())
	{
		m_RecentFiles.push_back(filename);
	}
}


void NodeGraphPanel::SaveGraph(const std::string& filename)
{
	/*GraphSerializer serializer(m_Nodegraph);
	serializer.Serialize(filename);
	m_LastFileUsed = filename;
	SaveToRecentFiles(filename);*/
}

void NodeGraphPanel::LoadGraph(const std::string& filename)
{
	/*m_Nodegraph.reset();
	m_Nodegraph = MakeRef<NodeGraph>();
	GraphSerializer serializer(m_Nodegraph);
	serializer.DeSerialize(filename);
	m_LastFileUsed = filename;
	SaveToRecentFiles(filename);*/
}

void NodeGraphPanel::SavePrefs()
{
	YAML::Emitter out;
	out << YAML::BeginMap;

	out << YAML::Key << "Recent Files";
	out << YAML::Value << YAML::BeginSeq;

	for (auto file : m_RecentFiles)
	{
		out << file;
	}

	out << YAML::EndSeq;
	out << YAML::EndMap;

	out << YAML::EndMap;

	std::ofstream fout("Prefs/Pref.ini");
	fout << out.c_str();
}

void NodeGraphPanel::LoadPrefs()
{
	if (!std::filesystem::exists("Prefs"))
	{
		std::filesystem::create_directory("Prefs");
	}

	std::ifstream stream("Prefs/Pref.ini");
	std::stringstream strstream;
	strstream << stream.rdbuf();

	YAML::Node data = YAML::Load(strstream.str());

	auto files = data["Recent Files"];
	if (files)
	{
		for (auto file : files)
		{
			m_RecentFiles.push_back(file.as<std::string>());
		}
	}
}

