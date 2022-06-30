#pragma once

#include <Engine.h>
#include "Layer.h"
#include "ImGui/WindowStack.h"

class GraphLayer : public BHive::Layer
{
public:
	GraphLayer();

	void OnAttach() override;

	void OnDetach() override;

	void OnUIRender() override;

private:
	WindowStack m_WindowStack;
};
