#pragma once


#include "Layouts.h"

struct BoxStyle
{
	bool m_Filled = true;
	
	bool m_RoundingTL = false;
	
	bool m_RoundingTR = false;
	
	bool m_RoundingBL = false;
	
	bool m_RoundingBR = false;

	float m_Rounding = 0.0f;

	float m_Thickness = 1.0f;

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