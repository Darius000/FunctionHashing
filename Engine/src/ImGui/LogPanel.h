#pragma once

#include "Core/Core.h"
#include "ImGuiPanel.h"

class LogPanel : public ImGuiPanel
{

public:
	LogPanel(const std::string& label, ImGuiWindowFlags flags, ImGuiID id = 1, bool runtimecreated = false);

	void OnRenderWindow() override;


	
	void OnRenderMenuBar() override;


};

