#pragma once

#include <Engine.h>
#include "ImGui/WindowStack.h"

class GraphLayer : public Layer
{
public:
	GraphLayer();

	void OnAttach() override;

	void OnDetach() override;

	void OnUpdate(float deltaTime) override;

	void OnImGuiRender() override;

	void ProcessEvents(Event& e) override;

private:
	WindowStack m_WindowStack;

	bool b_ShowDemoWindow;
};
