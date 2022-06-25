#ifndef CIRCLEELEMENT_H
#define CIRCLEELEMENT_H

#include "UIElement.h"

struct CircleStyle
{
	Value<float> m_Radius = 1.0f;

	Value<uint32_t> m_Resolution = 12;

	Value<bool> m_Filled = false;

	Value<float> m_Thickness = 1.0f;
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

#endif //CIRCLEELEMENT_H