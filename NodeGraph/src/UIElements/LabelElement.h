#pragma once

#include "UIElement.h"

class LabelElement : public UIElement
{
public:

	LabelElement(std::string_view name, const std::string& text = "");

	void OnDrawElement() override;

	ImRect GetBounds() override;

	std::string m_Text = "";
};