#pragma once

#include "UIElement.h"

class LabelElement : public UIElement
{
public:

	LabelElement(const std::string& text = "");

	void OnDrawElement(ImDrawList* drawlist) override;

	std::string m_Text = "";
};