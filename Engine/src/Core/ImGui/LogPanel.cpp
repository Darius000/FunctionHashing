#include "PCH.h"
#include "LogPanel.h"


LogPanel::LogPanel(const std::string& label, ImGuiWindowFlags flags, ImGuiID id , bool runtimecreated )
	:ImGuiPanel(label, flags, id, runtimecreated)
{

}

void LogPanel::OnRenderWindow()
{

	ImGui::TextUnformatted(Log::GetBuffer().begin());

	if (Log::ScrollToBottom)
		ImGui::SetScrollHere(1.0f);
	Log::ScrollToBottom = false;
}


void LogPanel::OnRenderMenuBar()
{
	
}


