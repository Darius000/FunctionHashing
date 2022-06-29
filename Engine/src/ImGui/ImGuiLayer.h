#pragma once

#include "Core/Layer.h"
#include "WindowStack.h"

class ImGuiLayer : public Layer 
{

public:
	ImGuiLayer();

	void OnAttach() override;

	void OnUpdate(float deltaTime) override;

	void OnDetach() override;

	void ProcessEvents(Event& e) override;

	void OnBegin();

	void OnEnd();


};