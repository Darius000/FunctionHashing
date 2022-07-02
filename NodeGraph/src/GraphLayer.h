#pragma once

#include <Engine.h>
#include "Layer.h"
#include "ImGui/WindowStack.h"
//#include "Image.h"

//class BHive::Image;

class GraphLayer : public BHive::Layer
{
public:
	GraphLayer();

	void OnAttach() override;

	void OnDetach() override;

	void OnUIRender() override;

	//Ref<BHive::Image> m_ImageTest;

private:
	WindowStack m_WindowStack;
};
