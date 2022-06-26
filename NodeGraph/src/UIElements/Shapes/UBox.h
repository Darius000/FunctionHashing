#pragma once


#include "UIElements/Layouts/Layouts.h"

struct BoxStyle
{
	Value<bool> m_Filled = true;

	Value<bool> m_RoundingTL = false;

	Value<bool> m_RoundingTR = false;
	
	Value<bool> m_RoundingBL = false;
		
	Value<bool> m_RoundingBR = false;

	Value<float> m_Rounding = 0.0f;

	Value<float> m_Thickness = 1.0f;

	ImDrawFlags GetRoundingFlags() 
	{
		ImDrawFlags flags = 0;

		if (m_RoundingTL) flags |= ImDrawFlags_RoundCornersTopLeft;
		if (m_RoundingTR) flags |= ImDrawFlags_RoundCornersTopRight;
		if (m_RoundingBL) flags |= ImDrawFlags_RoundCornersBottomLeft;
		if (m_RoundingBR) flags |= ImDrawFlags_RoundCornersBottomRight;

		return flags;
	}
};

class UBox : public LayoutElement
{
public:

	UBox();

	void OnDrawElement() override;

	ImRect GetBounds();

	BoxStyle& GetBoxStyle() { return m_BoxStyle; }

private:

	BoxStyle m_BoxStyle;
};