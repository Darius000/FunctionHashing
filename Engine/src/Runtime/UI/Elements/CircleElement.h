#pragma once

#include "UIElement.h"

struct CircleStyle
{
	float m_Radius = 1.0f;

	uint32_t m_Resolution = 12;

	bool m_Filled = false;

	float m_Thickness = 1.0f;
};

class CircleElement : public UIElement
{
public:

	CircleElement(std::string_view name);

	void OnDrawElement() override;

	ImRect GetBounds();

	CircleStyle& GetCircleStyle() { return m_CircleStyle; }

private:

	CircleStyle m_CircleStyle;
};

